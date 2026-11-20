// Whitespace can change JavaScript control flow through automatic semicolon
// insertion. Check the parsed program as well as the interleaved tokens and
// comments, including literal spellings and comments between statements.
import { createHash } from 'node:crypto';

export function sourceLayoutSignature(parse, source) {
    const lexical = createHash('sha256');
    const program = parse(source, {
        ecmaVersion: 'latest',
        sourceType: 'module',
        onToken(token) {
            lexical.update(JSON.stringify(['token', source.slice(token.start, token.end)]));
        },
        onComment(block, value) {
            lexical.update(JSON.stringify([block ? 'block' : 'line', value.trimEnd()]));
        },
    });
    const syntax = JSON.stringify(program, (key, value) => {
        if (key === 'start' || key === 'end') return undefined;
        return typeof value === 'bigint' ? value.toString() : value;
    });
    return lexical.update(syntax).digest('hex');
}
