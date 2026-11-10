// Import * as nhlsel and createNhlselEnvironment in central wasm-runtime.js.
// Allocate const nhlselEnvironments = new WeakMap() inside createPortedRuntime.
nhlsel(services,name,...args) {
    let environment=nhlselEnvironments.get(services.moduleKey);
    if(!environment){environment=createNhlselEnvironment(services,layouts.nhlsel,nhlsel);nhlselEnvironments.set(services.moduleKey,environment);}
    if(name==='l_selection_push_copy')args[1]=environment.selection(args[1]);
    if(name==='params_sel_2coords'){
        const view=()=>new DataView(services.heap().buffer);
        args=args.map((p,i)=>{
            if(!i)return p;
            const at=Number(p);
            return {get value(){return i===1?environment.selection(Number(view().getBigUint64(at,true))):view().getInt16(at,true);},set value(v){if(i===1)view().setBigUint64(at,BigInt(v?.address??v??0),true);else view().setInt16(at,Number(v),true);}};
        });
    }
    const result=withCEnvironment(environment,nhlsel[name],...args);
    return name==='l_selection_check'||name==='l_selection_push_new'?result?.address??0:result;
},
