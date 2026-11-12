// Preserve tu-strutil-probe.c's fixture and panic boundary in JavaScript.
import {environment,probeModule} from './common.mjs';
export default async function createStrutilProbe(){
 const env=await environment(),message=env.memory.calloc(1,256),buffer=p=>env.strbuf(Number(p));
 const methods={_probe_init:p=>env.strutil('strbuf_init',buffer(p)),_probe_append:(p,s)=>env.strutil('strbuf_append',buffer(p),Number(s)),_probe_reserve:(p,n)=>env.strutil('strbuf_reserve',buffer(p),n),_probe_empty:p=>env.strutil('strbuf_empty',buffer(p)),_probe_crlf:p=>env.strutil('strbuf_nl_to_crlf',buffer(p)),_probe_match:(p,s,ci)=>env.strutil(ci?'pmatchi':'pmatch',Number(p),Number(s)),_probe_message:()=>BigInt(message),_probe_guarded_strlen(p){env.memory.HEAPU8[message]=0;try{return env.strutil('Strlen_',Number(p),'source-path.c',777);}catch(e){if(e.name!=='CPanic')throw e;env.memory.HEAPU8.set(Buffer.from(e.message+'\0'),message);return -1;}}};
 return probeModule(env,methods);
}
