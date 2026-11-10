# Pinned Unix compress/LZW codec

Unmodified files from ncompress 5.0:
https://github.com/vapier/ncompress/tree/v5.0
Archive: https://codeload.github.com/vapier/ncompress/tar.gz/refs/tags/v5.0
Archive SHA-256: `96ec931d06ab827fccad377839bfb91955274568392ddecf809e443443aead46`.

Vendored code hashes:
- compress.c: `41f593dcc4e21a3d2686010a554687231a498291268791c8db412bf5b5e5087f`
- patchlevel.h: `222354c13eb9c345feaf8d692f897f8ad05e12c10468f0693c56491d1ad35692`

The authors release this implementation into the public domain; preserve
UNLICENSE and LICENSE.txt. No download is needed during build or replay.

`../../compress-service.c` includes this source with renamed codec/main symbols
and intercepts exit via setjmp/longjmp. The CLI is never called. The wrapper
opens ordinary files, calls the codec, resets global codec state for each call,
closes descriptors and reports status to NetHack. The codec is synchronous and
not reentrant within a module; replay segments have separate Wasm instances. NetHack retains its own file
cleanup and prompts. The wrapper validates .Z magic, a complete initial code,
and supported bit widths (9–16) before decoding; errors do not terminate the
module. It emits block-mode 16-bit .Z, with exit status 2 for compression that
fails to shrink the input, matching the configured unforced CLI behavior.

This preserves .Z/LZW interoperability, not guaranteed byte-identical compressed
streams: compression implementations can choose different dictionary reset
points. Test both directions against the macOS /usr/bin tools. .Z has no checksum
or stored uncompressed length, so not every truncated or altered stream can be
detected; do not claim universal corruption detection.
