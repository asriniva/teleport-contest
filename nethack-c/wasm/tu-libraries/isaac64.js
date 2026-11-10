// isaac64 ABI declarations only; game logic is in js/ported/isaac64.js.
addToLibrary({
  isaac64_init__sig: 'vppi',
  isaac64_init: function(_ctx, _seed, _nseed) {
    Module['nethackPorted'].isaac64_init(HEAPU8, _ctx, _seed, _nseed);
  },
  isaac64_reseed__sig: 'vppi',
  isaac64_reseed: function(_ctx, _seed, _nseed) {
    Module['nethackPorted'].isaac64_reseed(HEAPU8, _ctx, _seed, _nseed);
  },
  isaac64_next_uint64__sig: 'jp',
  isaac64_next_uint64: function(_ctx) {
    return Module['nethackPorted'].isaac64_next_uint64(HEAPU8, _ctx);
  },
  isaac64_next_uint__sig: 'jpj',
  isaac64_next_uint: function(_ctx, _n) {
    return Module['nethackPorted'].isaac64_next_uint(HEAPU8, _ctx, _n);
  },
});
