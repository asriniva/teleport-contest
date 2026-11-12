# Executed native signal proof sources

`executed-source-manifest.json` binds the exact executed test sources, C probe,
compiler command, SDK/native measurement and reference sources, and fresh R5
receipts retained here. Native binaries are not shipped. Rebuilding the oracle
requires the pinned installed SDK/system cache and the sealed original-C
reference described in the native receipts. `native/command.json` records the
actual build command; recorded local paths identify the original run and must
be relocated explicitly when reproducing elsewhere.

These are exact executed artifacts, not a claim of a newly tested portable
build wrapper. The separately proposed convenience wrappers remain outside this
checkpoint. Production execution uses neither this C oracle nor its SDK.
