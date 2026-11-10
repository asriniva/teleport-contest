// Imports required in wasm-runtime.js: import {callEnd} from './end-runtime.js';
        end(services,name,...args) {return callEnd(services,layouts.end,name,...args);},
