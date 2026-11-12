# Completed pre-completion C-runtime cleanup plan

This plan belongs to the preceding cleanup checkpoint. The later [services/binding cleanup](SERVICES_CLEANUP_PLAN.md) records the completed ownership and factory follow-up.

Scope: complete the cleanup that can precede full pure-JS game acceptance.
Work only in `cleanup/c-runtime-rect`; preserve original game function bodies,
C behavior, upstream/frozen inputs and other agents' worktrees.

| Step | Status | Completion evidence |
| --- | --- | --- |
| Define common runtime and application declaration boundaries | Complete | Public index, factory, NetHack declaration layer, import-closure guard |
| Consolidate standalone memory, types, callbacks and record machinery | Complete | Shared record/indexed-view implementation; contract and C comparisons |
| Centralize stdio/libc/scanning/sorting and symbol/global linking | Complete | Mechanical factory audit, native libc and configured-C scanner tests |
| Replace duplicated address transport with schema-driven bindings | Complete |13 existing adapters,23,700 original-C checks |
| Consolidate repeated generic helpers in translation-specific adapters | Complete |18 shared helpers replace132 exact bodies across58 adapters; full inverse/syntax audit and57 passing C suites; baseline LIGHT failure retained |
| Remove compatibility files with no consumers; retain required APIs | Complete | Six unused files retired, eight consumer/tool migrations audited; required entry APIs preserved |
| Reconcile owned provenance, source guards and reproducible generation | Complete |215-source manifest,72 provenance outputs, exact historical inverses, actual exporters and strict finite-profile negatives pass |
| Verify rebased integration and report exact source-size impact | Complete |19 focused/game checks, aggregate source scope,47-case pager and level persistence pass; raw production JS −5,491 bytes against latest rebased main8cf4880 |

Retirement gate, outside this pre-completion cleanup: remove the mixed backend
and its live bridges only after complete pure-JS game acceptance. Existing
translation-specific game/header policies remain application bindings, not C
runtime algorithms. Required compatibility aliases may remain; duplicated
implementations should not.

Validation history and limitations are in `C_RUNTIME_CLEANUP.md` and
`c-runtime-validation.json`. Historical failed attempts are retained; current
source-scope checks pass. LIGHT remains an explicitly failing baseline component.
Latest rebase validation is recorded separately in
`c-runtime-rebase-validation.json`. Main's exact approved VISION correction is
preserved without refreshing the original scope baseline. No full registry/
standalone aggregate execution, public44 acceptance, arbitrary game/native-host
parity or speed improvement is claimed.
