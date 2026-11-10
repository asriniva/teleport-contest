# MKOBJ pre-free payload observation diagnosis

The initial added wrapper spy copied still-allocated object payload immediately
before calling real libc free. That new observation found JS zeroed bytes and
original -O2 C old bytes. The source assignment `*obj = cg.zeroobj` at mkobj.c2825
remains intact in JS. This is not called an original-source algorithm defect or
an observation after object lifetime ended: a link-time `--wrap=free` does not
remove the compiler's builtin-libc assumptions while compiling the call site.

Fresh actual production-profile IR (cwd TREE/src, basename mkobj.c, forced native
terminal/ncurses profile, -O2 -g memory64) in production-original-o2.ll inlines
`dealloc_obj_real`. Lines8323–8337 optionally call dealloc_oextra then call free,
with no zero store/memcpy. Metadata !6609 maps that free to source2826. The private
fixture IR retains a named dealloc_obj_real at11372–11385 with the same absence.
No no-builtin, lower optimization or changed C algorithm was used to match JS.

The original builder link flags at nethack-c/wasm/build.py173 contain no free
wrapping, alternate allocator or tracing option. SDK src/settings.js132 defaults
to dlmalloc. Its system/lib/dlmalloc.c4772 dlfree operates on allocator headers
and free-bin links; its free tracing macro is disabled without tracing
(system/include/emscripten/trace.h83). No production object-payload spy was found.
This is a bounded source/toolchain inspection, not a new native allocator run.

The accepted comparison excludes ONLY the additional pre-free payload-content
spy. It retains exact allocation/free events, live/dead ownership, sizes/kinds,
all still-live object/monster/allocation bytes and their typed pointer mappings.
It does not claim equivalent post-free allocator payload or native use-after-free
behavior. The original source's comment about intended stale-memory/UAF detection
is retained. The wrapper's saved bytes remain a diagnostic export; final tests
never read freed storage and do not compare the optimizer-sensitive saved bytes.

The first failure and both exact IR files are preserved with these hashes:
- .cache/mkobj-first-pass/initial-prefree-dead-store.log SHA256 `edeaeceecacdbd5327be7926ad45e5b88fe80cbfbd506e9f84d17d4b63e1ac6b`
- .cache/mkobj-first-pass/production-original-o2.ll SHA256 `74173a5d8871591e2c3ff1458013ef871e0144cce306fe3aa8f958d7f193843d`
- .cache/mkobj-first-pass/original-o2.ll SHA256 `9ba1cc2ecd29c9e909578dd372c7931ce0547b70eb45e7348a8a72d8048fefaa`
