Focused callback/address boundary audit

No confirmed production call path was found that forwards a record carrier object into address-only code without a later conversion. This is a focused audit, not an exhaustive dynamic assertion for every game branch.

Confirmed conversions on the timeout-related APPLY path:

- js/nethack/bindings/apply.js:272–276 replaces function arguments with registered callback IDs. Non-function record/ref carriers deliberately remain until the typed bridge.
- js/nethack/apply.js:16–17 maps every foreign argument using its ABI type. Pointer arguments go through text(value), then environment.address(value), which unwraps .address (js/c-runtime/memory.js:5–8). Return pointers are also normalized there.
- js/ported/dothrow.js:527–532 normalizes all walk_path pointer inputs using C.ptr, including callback and void* argument; :580/:593 forwards the normalized numeric argument to the indirect callback.
- js/nethack/getpos.js:27 normalizes the function pointer and narrows x/y before callValid. APPLY callback entry normalization is in js/nethack/bindings/apply.js:315–328, including void* at :320 and struct-pointer record materialization.
- js/nethack/address-ports.js:53 specifically normalizes MKOBJ public pointer arguments before its native-address policies. The address-binding foreign dependency return path (js/c-runtime/address-bindings.js:58) unwraps pointer return carriers with environment.address.

Potential generic API gaps, with no confirmed object-producing game caller found:

- js/c-runtime/functions.js:15 validates callback ID/signature but forwards ...args unchanged; it is a function registry, not an ABI marshaller.
- js/c-runtime/address-bindings.js:51–56 forwards indirect/callback arguments unchanged, and :58 forwards foreign dependency arguments unchanged. Their translated-source contract is that arguments already have the address/scalar representation. Arbitrary external callers could violate that contract.
- js/nethack/schema-port.js:28–29 similarly marshals return values, not incoming foreign/indirect arguments. Its TRAP producer casts pointer values to numeric addresses (js/nethack/bindings/trap.js:13,18–19); raw argument forwarding alone is not evidence of a game bug.
- Some address-only pointer readers reject .address-only objects rather than unwrap them: e.g. INVENT ptr at js/nethack/bindings/invent.js:12 uses Number(v)/BigInt(v), while TRAP address at bindings/trap.js:13 uses Number(v). Intentional scalar-adapter carriers may supply a numeric primitive conversion; a plain {address: n} is not interchangeable with every native pointer input. A concrete producer-to-consumer trace is required before changing these profiles.

No new unimplemented callback was identified. Parent separately verified the availability and registered IDs for all 23 APPLY ABI callbacks. No production source was modified and no benchmark was run for this audit.
