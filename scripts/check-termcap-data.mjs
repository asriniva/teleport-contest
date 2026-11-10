import {checkTermcapSource} from '../nethack-c/wasm/tu-fragments/termcap-source-check.mjs';
console.log(JSON.stringify(checkTermcapSource(process.cwd(),{preprocess:!process.argv.includes('--no-preprocess'),ast:!process.argv.includes('--no-ast')})));
