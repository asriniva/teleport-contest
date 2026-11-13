// Original C needs its reference Wasm runtime. Unused lazy networking globals
// are removed before any test temporarily denies capabilities to pure JS.
for(const name of ['fetch','WebSocket','XMLHttpRequest','Worker'])delete globalThis[name];
