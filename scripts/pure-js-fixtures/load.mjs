import createProbe from './runtime.mjs';
import createReference from './reference.mjs';
export {createProbe,createReference};
export async function loadFixture(name,url){
 if(typeof url==='string'&&url.startsWith('.'))url=new URL(url,new URL('../test-tu-'+name+'.mjs',import.meta.url));
 const value=String(url);
 if(/(?:^|[/_-])hybrid(?:[._/-]|$)/.test(value))return {default:options=>createProbe(name,options)};
 if(/(?:^|[/_-])reference(?:[._/-]|$)/.test(value))return {default:options=>createReference(name,url,options)};
 return import(typeof url==='string'&&url.startsWith('.')?new URL(url,new URL('../test-tu-'+name+'.mjs',import.meta.url)):url);
}
export async function fixtureImports(name){
 const {readFile}=await import('node:fs/promises');
 const abi=JSON.parse(await readFile(new URL(`../../.cache/pure-js-fixtures/${name}/abi.json`,import.meta.url)));
 return Object.keys(abi.imports).map(name=>({name,kind:'function'}));
}
