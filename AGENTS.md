# Change transparency

The user requires a clear, maintained list of every divergence from upstream
and does not want edits made silently.

- Before editing, explain the concrete changes you intend to make, their
  purpose, and any behavior or capability that will change. Do not describe
  stubs, disabled facilities, or partial implementations as full support.
- Maintain `UPSTREAM_DIVERGENCES.md` in the same change as any divergence.
  Include source changes made indirectly by build scripts, compiler flags,
  generated configuration, runtime adapters, dependencies, and defaults.
- Distinguish inherited contest patches from changes added in this workspace.
  Distinguish the pristine reference checkout from the modified source that
  actually gets compiled. An unchanged submodule does not mean an unmodified
  executable.
- For each new or revised entry, record its location, exact change, reason,
  behavioral effect, limitations, and verification. Identify untested claims.
- Explain completed changes and checks afterward. State unresolved defects
  plainly. Keep retired/replaced decisions in the register's history.
- Announcing an authorized change does not by itself require another approval
  request; follow the user's existing authorization and task scope.

- Treat recording equivalence as a requirement. Build success or passing smoke
  tests is not evidence of equivalence. Report degraded public scores clearly.
- When replacing a dependency, explicitly state which reference behavior is
  preserved, changed, omitted or unverified. A compilation workaround is not
  automatically behavior-preserving or required by the target platform.
- Put active defaults and current validation results near the top of the
  divergence register. Label historical scores and proposed fixes explicitly.
- Keep terminal capability selection, input/output transport, shadow recording,
  terminal emulation and snapshot serialization distinct in explanations.
