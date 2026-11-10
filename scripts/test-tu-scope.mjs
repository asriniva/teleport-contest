#!/usr/bin/env node
// Conservative lexical-name check for registered translated TUs, not an
// equivalence proof or a full JavaScript type/semantic check. Acorn is an SDK
// development dependency only; this script is never imported by the game.
// It does not check temporal dead zones, initialization order, member names,
// dynamic property lookup, types, or whether imported modules/exports exist.
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const sdk = resolve(process.env.EMSDK ?? join(root, '.cache/emsdk'));
const { parse, version } = await import(pathToFileURL(join(sdk,
    'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);

// Deliberately do not allow browser, Node, Wasm or game globals. Those must be
// imported or accessed through the TU's explicit C environment.
const builtins = new Set([
    'undefined', 'NaN', 'Infinity', 'Math', 'BigInt', 'Number', 'Boolean',
    'Int8Array', 'Int32Array', 'Uint8Array', 'BigUint64Array',
]);

function checkSource(source, filename) {
    const tree = parse(source, { ecmaVersion: 'latest', sourceType: 'module', locations: true });
    const references = [];
    const makeScope = (parent, kind = 'block') => ({ parent, kind, bindings: new Set() });
    const moduleScope = makeScope(null, 'module');
    const varScope = scope => {
        while (scope.kind === 'block') scope = scope.parent;
        return scope;
    };
    const reference = (node, scope) => references.push({ node, scope });

    // Binding patterns are distinct from assignment patterns. Computed keys
    // and default values still contain executable references in evalScope.
    function bind(pattern, target, evalScope) {
        if (!pattern) return;
        switch (pattern.type) {
        case 'Identifier': target.bindings.add(pattern.name); break;
        case 'RestElement': bind(pattern.argument, target, evalScope); break;
        case 'AssignmentPattern':
            bind(pattern.left, target, evalScope);
            visit(pattern.right, evalScope);
            break;
        case 'ArrayPattern':
            for (const element of pattern.elements) bind(element, target, evalScope);
            break;
        case 'ObjectPattern':
            for (const property of pattern.properties) {
                if (property.type === 'RestElement') bind(property.argument, target, evalScope);
                else {
                    if (property.computed) visit(property.key, evalScope);
                    bind(property.value, target, evalScope);
                }
            }
            break;
        default: throw new Error(`${filename}: unsupported binding pattern ${pattern.type}`);
        }
    }

    function visitFunction(node, outer) {
        if (node.type === 'FunctionDeclaration' && node.id) outer.bindings.add(node.id.name);
        const parameters = makeScope(outer);
        if (node.id) parameters.bindings.add(node.id.name);
        if (node.type !== 'ArrowFunctionExpression') parameters.bindings.add('arguments');
        for (const parameter of node.params) bind(parameter, parameters, parameters);
        // Body var declarations are hoisted within the function, but do not
        // leak into default-parameter initializers.
        const body = makeScope(parameters, 'function');
        if (node.body.type === 'BlockStatement')
            for (const statement of node.body.body) visit(statement, body);
        else visit(node.body, body);
    }

    function visit(node, scope) {
        if (!node) return;
        switch (node.type) {
        case 'Identifier': reference(node, scope); return;
        case 'PrivateIdentifier':
        case 'Literal':
        case 'MetaProperty':
        case 'BreakStatement':
        case 'ContinueStatement': return;
        case 'Program':
            for (const statement of node.body) visit(statement, scope);
            return;
        case 'ImportDeclaration':
            for (const specifier of node.specifiers) bind(specifier.local, scope, scope);
            return;
        case 'ExportNamedDeclaration':
            if (node.declaration) visit(node.declaration, scope);
            if (!node.source)
                for (const specifier of node.specifiers) visit(specifier.local, scope);
            return;
        case 'ExportAllDeclaration': return;
        case 'ExportDefaultDeclaration': visit(node.declaration, scope); return;
        case 'VariableDeclaration':
            for (const declaration of node.declarations) {
                bind(declaration.id, node.kind === 'var' ? varScope(scope) : scope, scope);
                visit(declaration.init, scope);
            }
            return;
        case 'FunctionDeclaration':
        case 'FunctionExpression':
        case 'ArrowFunctionExpression': visitFunction(node, scope); return;
        case 'BlockStatement': {
            const block = makeScope(scope);
            for (const statement of node.body) visit(statement, block);
            return;
        }
        case 'StaticBlock': {
            const block = makeScope(scope, 'function');
            for (const statement of node.body) visit(statement, block);
            return;
        }
        case 'CatchClause': {
            const caught = makeScope(scope);
            bind(node.param, caught, caught);
            visit(node.body, caught);
            return;
        }
        case 'ForStatement':
        case 'ForInStatement':
        case 'ForOfStatement': {
            const loop = makeScope(scope);
            for (const key of ['init', 'left', 'right', 'test', 'update', 'body']) visit(node[key], loop);
            return;
        }
        case 'SwitchStatement': {
            visit(node.discriminant, scope);
            const cases = makeScope(scope);
            for (const branch of node.cases) visit(branch, cases);
            return;
        }
        case 'ClassDeclaration':
        case 'ClassExpression': {
            if (node.type === 'ClassDeclaration' && node.id) scope.bindings.add(node.id.name);
            const local = makeScope(scope);
            if (node.id) local.bindings.add(node.id.name);
            visit(node.superClass, local);
            visit(node.body, local);
            return;
        }
        case 'Property':
        case 'MethodDefinition':
        case 'PropertyDefinition':
        case 'AccessorProperty':
            if (node.computed) visit(node.key, scope);
            visit(node.value, scope); // Includes shorthand and assignment-target references.
            return;
        case 'MemberExpression':
            visit(node.object, scope);
            if (node.computed) visit(node.property, scope);
            return;
        case 'LabeledStatement': visit(node.body, scope); return;
        }
        // Remaining expression/statement children have no binding positions.
        // typeof intentionally follows this path: unknown globals are errors
        // even when JavaScript would permit probing their existence.
        for (const value of Object.values(node)) {
            if (Array.isArray(value)) {
                for (const child of value) if (child?.type) visit(child, scope);
            } else if (value?.type) visit(value, scope);
        }
    }

    visit(tree, moduleScope);
    // Resolve only after collecting every declaration, so forward function
    // references and var hoisting do not cause spurious undeclared errors.
    return references.filter(({ node, scope }) => {
        for (; scope; scope = scope.parent) if (scope.bindings.has(node.name)) return false;
        return !builtins.has(node.name);
    }).map(({ node }) => ({ filename, name: node.name,
        line: node.loc.start.line, column: node.loc.start.column + 1 }));
}

// Tiny in-memory tooling fixtures, independent of game algorithms.
const fixtures = [
    ['bare C globals', 'import { C } from "x"; C.distant_name(C.obj, doname); if (uarm) C.f(uarmf);', ['doname', 'uarm', 'uarmf']],
    ['typeof policy', 'typeof missing;', ['missing']],
    ['property and label names', 'import { C } from "x"; top: for (let i=0;i<2;i++) { C.uarm; C[i]; break top; }', []],
    ['shorthand and computed references', 'const local=1; ({plain: local, local, [missingKey]: missingValue});', ['missingKey', 'missingValue']],
    ['hoisting and lexical escape', 'function f(){ before(); if(true){ var v=1; let hidden=2; } function before(){} return v + hidden; }', ['hidden']],
    ['parameters and destructuring', 'import def, {x as imported} from "x"; export function f({a: renamed=imported,...rest},[first],...tail){ const {[renamed]: picked}=rest; return ()=>[picked,first,tail,def]; }', []],
    ['parameter defaults exclude body vars', 'function f(a=bodyOnly){var bodyOnly;return a;}', ['bodyOnly']],
    ['catch and loop scopes', 'try{}catch({message}){message;} message; for(let index of []){index;} index;', ['message', 'index']],
    ['assignment destructuring', 'let local; ({name: local, other: unknown}= {});', ['unknown']],
    ['named expressions and arguments', 'const f=function inside(){return ()=>[inside,arguments]}; const c=class Named{method(){return Named}}; inside; Named;', ['inside', 'Named']],
    ['exports', 'export {external as alias} from "x"; const local=1; export {local as publicName};', []],
];
for (const [name, source, expected] of fixtures)
    assert.deepEqual(checkSource(source, `<scope fixture: ${name}>`).map(error => error.name), expected, name);

const ports = JSON.parse(await readFile(join(root, 'nethack-c/wasm/tu-ports.json'), 'utf8'));
let errors = 0;
for (const port of ports) {
    const filename = join(root, port.javascript);
    let failures;
    try { failures = checkSource(await readFile(filename, 'utf8'), filename); }
    catch (error) {
        console.error(`${filename}:${error.loc?.line ?? 1}:${(error.loc?.column ?? 0) + 1}: ${error.message}`);
        errors++;
        continue;
    }
    for (const error of failures) {
        console.error(`${error.filename}:${error.line}:${error.column}: undeclared identifier '${error.name}'`);
        errors++;
    }
}
if (errors) process.exitCode = 1;
else console.log(`Lexical scope check passed: ${ports.length} registered TUs, ${fixtures.length} tooling fixtures (Acorn ${version}).`);
