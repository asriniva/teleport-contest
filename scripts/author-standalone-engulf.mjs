// Development-only native author: literal keyboard input and read-only observers.
// Wizard commands create the form/target through original game policy.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {gzipSync} from 'node:zlib';
import {runFullOriginalC} from './full-original-c-run.mjs';

const records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',argv:['-D','-u','Ada-male-lawful','-p','Archeologist','-r','human']};
let roots,pending='',phase='polymorph',created=false,attacks=0;
const decisions=[];
const directions={'-1,-1':'y','0,-1':'k','1,-1':'u','-1,0':'h','1,0':'l','-1,1':'b','0,1':'j','1,1':'n'};
const result=await runFullOriginalC('.cache/full-original-c-v1',{
    ...input,maxInputBoundaries:250,
    authorKey({module:m,state,frame,consumed}) {
        if(consumed<5)return 'yy  n'.charCodeAt(consumed);
        if(!roots) {
            roots={};
            for(let i=0;i<m._full_global_count();i++) {
                let p=Number(m._full_global_name(i)),end=p;
                while(m.HEAPU8[end])end++;
                roots[Buffer.from(m.HEAPU8.slice(p,end)).toString()]=Number(m._full_global_address(i));
            }
        }
        const v=new DataView(m.HEAPU8.buffer),field=(t,p,n)=>p+records[t].fields[n].offset;
        const inputState=v.getInt32(field('sinfo',roots.program_state,'input_state'),true);
        const emit=text=>{pending=text;const key=pending.charCodeAt(0);pending=pending.slice(1);return key;};
        if(pending)return emit(pending);
        const screen=String(frame?.screen??'');
        if(inputState!==layouts.cmd.commandInp) {
            if(phase==='form-prompt'&&/Become what kind|what kind of monster/i.test(screen)) {
                phase='create';return emit('purple worm\n');
            }
            if(phase==='monster-prompt'&&/Create what kind of monster/i.test(screen)) {
                phase='attack';return emit('hostile troll\n');
            }
            return 32;
        }
        if(phase==='polymorph'){phase='form-prompt';return emit('#polyself\n');}
        if(phase==='create'){phase='monster-prompt';return emit('#wizgenesis\n');}
        if(phase!=='attack')throw Error('Unexpected command prompt in phase '+phase);
        const list=field('dlevel_t',field('instance_globals_saved_l',roots.svl,'level'),'monlist');
        let target;const observed=[];
        for(let p=Number(v.getBigUint64(list,true));p;p=Number(v.getBigUint64(field('monst',p,'nmon'),true))) {
            const data=Number(v.getBigUint64(field('monst',p,'data'),true));
            const index=v.getInt32(field('permonst',data,'pmidx'),true);
            // The compiler-measured name pointer is observed, never assigned.
            const nameAt=field('permonst',data,'pmnames')+2*8;
            const name=Number(v.getBigUint64(nameAt,true));let end=name;while(m.HEAPU8[end])end++;
            const monsterName=Buffer.from(m.HEAPU8.slice(name,end)).toString();observed.push({index,monsterName});
            if(monsterName!=='troll')continue;
            target={id:v.getUint32(field('monst',p,'m_id'),true),index,
                x:v.getInt16(field('monst',p,'mx'),true),y:v.getInt16(field('monst',p,'my'),true)};
        }
        if(!target){assert.ok(created,'Original wizard command must create a troll: '+JSON.stringify(observed));return undefined;}
        created=true;
        const dx=target.x-state.x,dy=target.y-state.y,key=directions[dx+','+dy];
        assert.ok(key,'Original creation places the target adjacent');
        assert.ok(attacks++<12,'Bounded original attacks');
        decisions.push({keyIndex:consumed,kind:'attack',target,moves:state.moves,x:state.x,y:state.y});return key.charCodeAt(0);
    },
});
const out='.cache/engulf-author';fs.mkdirSync(out,{recursive:true});
fs.writeFileSync(out+'/result.json.gz',gzipSync(JSON.stringify(result)));
const text=Buffer.from(result.stdout,'base64').toString().replace(/\x1b\[[0-?]*[ -/]*[@-~]/g,'');
fs.writeFileSync(out+'/terminal.txt',text);
fs.writeFileSync(out+'/candidate.json',JSON.stringify({...input,keys:result.input.keys},null,2)+'\n');
console.log(JSON.stringify({status:result.status,consumed:result.consumed,attacks,decisions,terminalTail:text.slice(-1800)}));
assert.equal(result.status.kind,'input-exhausted');
assert.match(text,/swallow[^\n]*troll/i,'Actual original-C engulf message');
assert.ok(result.frames.some(f=>f.animation),'Actual animation boundaries captured');
