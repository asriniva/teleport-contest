#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
EMSDK="${EMSDK:-$ROOT/.cache/emsdk}"
if [[ -f "$EMSDK/emsdk_env.sh" ]]; then
    source "$EMSDK/emsdk_env.sh" >/dev/null 2>&1
fi
cd "$ROOT"
python3 -B scripts/test-tu-structure.py
node scripts/test-tu-scope.mjs
python3 -B scripts/build-tu-probes.py
node scripts/test-tu-isaac64.mjs
node scripts/test-tu-nhmd4.mjs
node scripts/test-tu-strutil.mjs
node scripts/test-tu-rect.mjs
node scripts/test-tu-track.mjs
node scripts/test-tu-calendar.mjs
node scripts/test-tu-stairs.mjs
node scripts/test-tu-sys.mjs
node scripts/test-tu-rip.mjs
node scripts/test-tu-date.mjs
node scripts/test-tu-alloc.mjs
node scripts/test-tu-utf8map.mjs
node scripts/test-tu-drawing.mjs
node scripts/test-tu-posixregex.mjs
node scripts/test-tu-rnd.mjs
node scripts/test-tu-ioctl.mjs
node scripts/test-tu-unixtty.mjs
node scripts/test-tu-were.mjs
node scripts/test-tu-extralev.mjs
node scripts/test-tu-mplayer.mjs
node scripts/test-tu-exper.mjs
node scripts/test-tu-mkmap.mjs
node scripts/test-tu-getline.mjs
node scripts/test-tu-write.mjs
node scripts/test-tu-mdlib.mjs
node scripts/test-tu-quest.mjs
node scripts/test-tu-minion.mjs
node scripts/test-tu-iactions.mjs
node scripts/test-tu-selvar.mjs
node scripts/test-tu-steal.mjs
node scripts/test-tu-sit.mjs
node scripts/test-tu-fountain.mjs
node scripts/test-tu-objects.mjs
node scripts/test-tu-monst.mjs
node scripts/test-tu-shknam.mjs
node scripts/test-tu-rumors.mjs
node scripts/test-tu-music.mjs
node scripts/test-tu-version.mjs
node scripts/test-tu-coloratt.mjs
node scripts/test-tu-priest.mjs
node scripts/test-tu-light.mjs
node scripts/test-tu-lock.mjs
node scripts/test-tu-steed.mjs
node scripts/test-tu-wizard.mjs
node scripts/test-tu-worm.mjs
node scripts/test-tu-o_init.mjs
node scripts/test-tu-ball.mjs
node scripts/test-tu-mcastu.mjs
node scripts/test-tu-dbridge.mjs
node scripts/test-tu-mondata.mjs
node scripts/test-tu-hacklib.mjs
node scripts/test-native-existing.mjs
node scripts/test-version-bridge.mjs
python3 scripts/test-terminfo.py
node scripts/test-wasm-replay-support.mjs
node scripts/test-compress.mjs
exec node scripts/test-wasm.mjs
