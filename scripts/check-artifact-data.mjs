import { checkArtifactSource } from '../nethack-c/wasm/tu-fragments/artifact-source-check.mjs';
console.log(JSON.stringify(checkArtifactSource(process.cwd(),{preprocess:!process.argv.includes('--no-preprocess')})));
