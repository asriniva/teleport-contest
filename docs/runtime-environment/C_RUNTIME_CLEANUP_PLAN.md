# Pre-completion C-runtime cleanup plan

Scope: complete the cleanup that can precede full pure-JS game acceptance.
Work only in `cleanup/c-runtime-rect`; preserve original game function bodies,
C behavior, upstream/frozen inputs and other agents' worktrees.

| Step | Status | Completion evidence |
| --- | --- | --- |
| Define common runtime and application declaration boundaries | Complete | Public index, factory, NetHack declaration layer, import-closure guard |
| Consolidate standalone memory, types, callbacks and record machinery | Complete | Shared record/indexed-view implementation; contract and C comparisons |
| Centralize stdio/libc/scanning/sorting and symbol/global linking | Complete | Mechanical factory audit, native libc and configured-C scanner tests |
| Replace duplicated address transport with schema-driven bindings | Complete |13 existing adapters,23,700 original-C checks |
| Consolidate repeated generic helpers in translation-specific adapters | In progress | Exact-body inventory identifies integer conversions/cells and descriptor arrays; extraction must preserve source-specific conventions |
| Remove compatibility files with no consumers; retain required APIs | Pending | Literal-import and metadata/exporter audit; no active consumer broken |
| Reconcile owned provenance, source guards and reproducible generation | In progress | Dedicated manifest and scanner/WERE exporters; any further changes need strict old/new/inverse review |
| Verify rebased integration and report exact source-size impact | In progress |14 focused checks and genuine-main smoke pass; final checks after remaining edits |

Retirement gate, outside this pre-completion cleanup: remove the mixed backend
and its live bridges only after complete pure-JS game acceptance. Existing
translation-specific game/header policies remain application bindings, not C
runtime algorithms. Required compatibility aliases may remain; duplicated
implementations should not.

Validation history and limitations are in `C_RUNTIME_CLEANUP.md`. An existing
aggregate provenance failure is retained, never waived or relabeled a pass.
