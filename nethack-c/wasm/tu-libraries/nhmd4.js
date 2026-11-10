// nhmd4 ABI declarations only; game logic is in js/ported/nhmd4.js.
addToLibrary({
  nhmd4_init__sig: 'vp',
  nhmd4_init: function(ctx) {
    Module['nethackPorted'].nhmd4_init(HEAPU8, ctx);
  },
  nhmd4_update__sig: 'vppp',
  nhmd4_update: function(ctx, data, size) {
    Module['nethackPorted'].nhmd4_update(HEAPU8, ctx, data, size);
  },
  nhmd4_final__sig: 'vpp',
  nhmd4_final: function(ctx, result) {
    Module['nethackPorted'].nhmd4_final(HEAPU8, ctx, result);
  },
});
