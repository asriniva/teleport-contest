import {checkHackSource} from '../nethack-c/wasm/tu-fragments/hack-source-check.mjs';
console.log(JSON.stringify(checkHackSource(process.cwd(),{preprocess:!process.argv.includes('--no-preprocess'),ast:!process.argv.includes('--no-ast')})));
