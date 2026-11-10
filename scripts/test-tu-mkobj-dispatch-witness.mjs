import assert from 'node:assert/strict';

export async function verifyMkobjDispatch(ctx) {
    const {hybrid,reference,hf,schema,L,seen,nativeOverrides,pool,index,field,C,R,T,callMkobj,getMkobjEnvironment}=ctx;
    const services=seen.get(hybrid),object=pool(hybrid);
    const objKind=Object.keys(schema.schema).indexOf('obj');
    const blessed=schema.schema.obj.fields.findIndex(f=>f.name==='blessed');
    const cursed=schema.schema.obj.fields.findIndex(f=>f.name==='cursed');
    const invoke=(m,name,p)=>m._probe_action(index(name),BigInt(p),0n,0n,0n,0n,0n);
    field(hybrid,object,'obj','blessed',0);
    field(hybrid,object,'obj','cursed',0);
    const stack=services.stackSave(),reads=[];
    let nested=false;
    const outer=Object.create(services);
    outer.read=(kind,address,member)=>{
        if(kind===objKind && Number(address)===object && [blessed,cursed].includes(member)) {
            reads.push(member);
            if(!nested) {
                nested=true;
                assert.equal(BigInt(invoke(hybrid,'bcsign',object)),0n,'actual C caller reenters imported JS');
            }
            return 1n;
        }
        return services.read(kind,address,member);
    };
    assert.equal(callMkobj(outer,L,'bcsign',object),0,'outer override restored after native reentry');
    assert.deepEqual(reads,[blessed,cursed],'both outer field reads use outer services');
    assert.equal(callMkobj(services,L,'bcsign',object),0,'later canonical call has no stale override');
    assert.equal(services.stackSave(),stack);

    const throwing=Object.create(services);
    throwing.read=()=>{throw new Error('MKOBJ directed current-service failure');};
    assert.throws(()=>callMkobj(throwing,L,'bcsign',object),/directed current-service failure/);
    assert.equal(callMkobj(services,L,'bcsign',object),0);
    assert.equal(services.stackSave(),stack);

    const reentering=Object.create(services);
    reentering.read=()=>invoke(hybrid,'bcsign',object);
    nativeOverrides.set(hybrid,{read:()=>{throw new Error('MKOBJ native nested failure');}});
    try {
        assert.throws(()=>callMkobj(reentering,L,'bcsign',object),/native nested failure/);
    } finally {nativeOverrides.delete(hybrid);}
    assert.equal(services.stackSave(),stack,'outer finally restores actual native caller frames');
    for(const value of[C,R,T])assert.equal(value,undefined);
    assert.equal(callMkobj(services,L,'bcsign',object),0);

    const environment=getMkobjEnvironment(services,L);
    const quantity=environment.field(object,'obj','quan');
    const cell=environment.cell(quantity.address,'long'),old=cell.value;
    const before=hybrid.HEAPU8.buffer;
    hybrid._probe_option(3,1n);
    invoke(hybrid,'next_ident',0);
    assert.notEqual(hybrid.HEAPU8.buffer,before,'actual native RNG hook grows memory');
    cell.value=9007199254741013n;
    assert.equal(quantity.value,9007199254741013n,'native field observes saved live view after growth');
    cell.value=old;
    assert.equal(callMkobj(services,L,'bcsign',object),0);

    let captured;
    const fresh=await hf({nethackPorted:{mkobj(s){captured=s;return 0;}}});
    fresh._probe_reset();invoke(fresh,'bcsign',pool(fresh));
    assert.ok(captured,'capture real services without constructing an environment');
    assert.throws(()=>getMkobjEnvironment(captured,{...L,pointerSize:4}),/changed MKOBJ ABI/);
    assert.throws(()=>getMkobjEnvironment(captured,{...L,pointerSize:4}),/changed MKOBJ ABI/);
    const valid=getMkobjEnvironment(captured,L);
    assert.ok(valid,'valid retry after failed constructors');
    assert.equal(callMkobj(captured,L,'bcsign',pool(fresh)),0);
    assert.equal(callMkobj(services,L,'bcsign',object),0,'second Module does not replace first services');
    assert.throws(()=>callMkobj(services,{...L},'bcsign',object),/layout identity/);
    assert.equal(services.stackSave(),stack);
    console.log('MKOBJ dispatcher witnesses PASS: native reentry, current services, nested throws, growth, Modules, constructor retry.');
}
