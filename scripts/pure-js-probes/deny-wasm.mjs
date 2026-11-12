if(process.env.TELEPORT_NATIVE_TESTS==='0')throw Error('Migrated pure-JS suites require the native original-C reference; Wasm diagnostics use legacy suites.');
// Optional process-wide isolation for migrated suites with a native C reference.
// --import runs before the test's dependency graph, including reference loaders.
for(const name of ['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'])Object.defineProperty(globalThis,name,{configurable:true,get(){throw Error('Unavailable capability in pure-JS test process: '+name);}});
