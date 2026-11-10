// Execute the compiled recorder inside a fresh Emscripten MEMFS per segment.
// Only seed, date, options, keys and the shared VFS cross this boundary.
import { createTerminalBackend } from './terminal-backend.js';
import { setStorageForTesting, vfsReadFile, vfsWriteFile } from './storage.js';
import { encodeRecorderScreen, recordingClockEpoch, shouldPersistGameFile } from './wasm-replay-support.js';
import { recordingProfile, profileSysconf } from './recording-profile.js';
import { createPortedRuntime } from './ported/wasm-runtime.js';
import tuLayouts from './wasm/tu-layouts.json' with { type: 'json' };

const STATE_PATH = '/teleport-wasm64-state.json';

function filesUnder(FS, directory, result = {}) {
    for (const name of FS.readdir(directory)) {
        if (name === '.' || name === '..') continue;
        const path = `${directory}/${name}`;
        const stat = FS.stat(path);
        if (FS.isDir(stat.mode)) filesUnder(FS, path, result);
        else if (FS.isFile(stat.mode)) result[path] = FS.readFile(path);
    }
    return result;
}

function encode(bytes) {
    // Chunk conversion to avoid argument-count limits for large save files.
    let binary = '';
    for (let i = 0; i < bytes.length; i += 8192) {
        binary += String.fromCharCode(...bytes.subarray(i, i + 8192));
    }
    return btoa(binary);
}

function decode(text) {
    return Uint8Array.from(atob(text), ch => ch.charCodeAt(0));
}

export async function runWasmSegment(input) {
    const useShadow = !(typeof process !== 'undefined' && process.env?.TELEPORT_TERMINAL === 'ghostty');
    const terminal = useShadow ? null : await createTerminalBackend();
    try {
        return await runWithTerminal(input, terminal);
    } finally { terminal?.dispose(); }
}

async function runWithTerminal(input, terminal) {
    const { default: createNethack } = await import('./wasm/nethack.mjs');
    // Emscripten recognizes this control-flow token without setting Node's
    // exit code to 1; the MEMFS state remains available for capture/persistence.
    const exhausted = 'unwind';
    const screens = [], cursors = [], animations = [];
    let pendingAnimations = [];
    let keyIndex = 0;
    const moves = input.moves || '';
    const diagnostics = [];
    const profile = recordingProfile();
    // Emscripten's libc time functions delegate to JS Date. In Node, Date
    // honors the host process TZ; expose the same zone to C's environment.
    const timezone = (typeof process !== 'undefined' && process.env?.TZ)
        || Intl.DateTimeFormat().resolvedOptions().timeZone;
    let baseline;
    setStorageForTesting(input.storage || null);
    const previousState = vfsReadFile(STATE_PATH);
    const module = await createNethack({
        nethackPorted: createPortedRuntime(tuLayouts),
        noInitialRun: true,
        stdout: terminal ? byte => terminal.writeByte(byte) : undefined,
        print: line => { diagnostics.push(line); if (diagnostics.length > 40) diagnostics.shift(); },
        printErr: line => diagnostics.push(line),
        teleportReadKey() {
            if (keyIndex >= moves.length) throw exhausted;
            const key = moves.charCodeAt(keyIndex++);
            return key === 13 ? 10 : key;
        },
        teleportCapture(screen, x, y, animation) {
            // The boundary hook supplies timing only for the emulator path.
            // Its shadow-buffer screen/cursor are ignored.
            const frame = terminal ? terminal.snapshot()
                : { screen: encodeRecorderScreen(screen), cursor: [x, y, 1] };
            if (animation) {
                pendingAnimations.push(frame);
            } else {
                screens.push(frame.screen);
                cursors.push(frame.cursor);
                animations.push(pendingAnimations);
                pendingAnimations = [];
            }
        },
        preRun: [instance => {
            const { FS, ENV } = instance;
            Object.assign(ENV, {
                NETHACKDIR: '/nethack', HACKDIR: '/nethack',
                HOME: profile.home, USER: 'root', LOGNAME: 'root',
                TERM: 'xterm-256color', TERMINFO: '/nethack/terminfo', LINES: '24', COLUMNS: '80', TZ: timezone,
                NETHACK_NO_DELAY: '1', NOMUX_MARKERS: '1',
                NETHACK_RAW_KEYS: '1', NETHACK_SEED: String(input.seed ?? 0),
                NETHACK_FIXED_DATETIME: input.datetime || '20000110090000',
                NETHACK_RECORDING_EPOCH: recordingClockEpoch(),
                NETHACK_RNGLOG: '/rng.log',
            });
            FS.mkdirTree(profile.home);
            FS.writeFile(`${profile.home}/.nethackrc`, input.nethackrc || '');
        }],
    });
    {
        const { FS } = module;
        FS.mkdirTree('/nethack/save');
        FS.chdir('/nethack');
        const sysconf = '/nethack/sysconf';
        FS.writeFile(sysconf, profileSysconf(FS.readFile(sysconf, { encoding: 'utf8' }), profile));
        baseline = filesUnder(FS, '/nethack');
        if (previousState) {
            const state = JSON.parse(previousState);
            for (const path of state.deleted) {
                try { FS.unlink(path); } catch { /* already absent */ }
            }
            for (const [path, data] of Object.entries(state.files)) {
                FS.mkdirTree(path.slice(0, path.lastIndexOf('/')));
                FS.writeFile(path, decode(data));
            }
        }
    }
    function readRng() {
        try { return module.FS.readFile('/rng.log', { encoding: 'utf8' }).split('\n').filter(Boolean).map(line => line.replace(/^\d+\s+/, '').replace(/\s*=\s*/g, '=')); }
        catch { return []; }
    }
    // -u with an empty name preserves the name-selection prompt.
    const name = /(?:^|[=\s,])name\s*:\s*([^,\n]+)/im.exec(input.nethackrc || '')?.[1]?.trim() || '';
    try {
        const status = module.callMain(['-u', name]);
        if (status) throw new Error(`Game exited with status ${status}: ${diagnostics.join('\n')}`);
    } catch (error) {
        if (error !== exhausted && !(error?.name === 'ExitStatus' && error.status === 0)) {
            throw new Error(`Wasm replay failed: ${error?.stack || error}\n${diagnostics.join('\n')}`);
        }
    }
    const rng = readRng();
    if (!screens.length) throw new Error(`Wasm produced no input boundaries. ${diagnostics.join('\n')}`);
    const after = filesUnder(module.FS, '/nethack');
    const state = { files: {}, deleted: Object.keys(baseline).filter(path => !(path in after)) };
    for (const [path, data] of Object.entries(after)) {
        // Level/lock files belong to the terminated game process. They must
        // not make the next segment think a previous player is still active.
        if (!shouldPersistGameFile(path)) continue;
        const original = baseline[path];
        if (!original || original.length !== data.length || data.some((byte, i) => byte !== original[i])) {
            state.files[path] = encode(data);
        }
    }
    vfsWriteFile(STATE_PATH, JSON.stringify(state));
    const terminalDiagnostics = terminal ? {
        backend: 'libghostty-vt 1.0.0',
    } : { backend: 'shadow' };
    return {
        getTerminalDiagnostics: () => terminalDiagnostics,
        getScreens: () => screens, getCursors: () => cursors,
        getRngLog: () => rng,
        getAnimationFramesByStep: () => animations,
    };
}
