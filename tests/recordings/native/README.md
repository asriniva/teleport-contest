# Supplemental native C recordings

These are native macOS arm64 NetHack 5.0 captures made with the contest patches
through `6ee30e6`. They live outside the leaderboard corpus. Each file
contains the complete input recipe together with the native recorder output.
Wizard commands arrange the starting items and forms. Actions then run through
ordinary game input.

```sh
node scripts/test-native-macos-replay.mjs tests/recordings/native/*.session.json
```

The test compares every screen, cursor and animation frame, and the ordered
PRNG values. The save and restore cases use fresh-native teardown semantics
and share one storage handle across both segments. The `status` save carries
blindness, confusion and hallucination into inventory and combat inputs.
The `lit-save-restore` save carries four active light sources into inventory
and apply inputs.

| Recording | Interactions |
| --- | --- |
| `artifacts` | Wear and invoke the Eye of the Aethiopica, wield and invoke Magicbane and Vorpal Blade |
| `bag-cancellation` | Put a cancellation wand into a bag of holding, handle the blast, potion prompt and wizard survival |
| `camera-mirror` | Aim a camera at the hero and the stairs, and aim a mirror at the hero and the ceiling |
| `corpse-genders` | Revive explicitly male and female newt corpses, using a downward zap |
| `genocide-earth` | Genocide lichens, drop boulders with a scroll of earth, then read cursed fire magic |
| `lit-save-restore` | Light an oil lamp, candles, a potion of oil and a lantern, then save, restore, inspect inventory and switch off lights |
| `lock-container` | Lock and unlock a floor chest, split a potion stack into it, inspect and retrieve the potion, grease inventory |
| `mounted-lance` | Leash and saddle a pony, mount it, wield a cursed lance, target an empty square at reach, then dismount |
| `music` | Improvise with a flute, horn, bugle and harp, then play a drum of earthquake |
| `naming` | Name an individual object, call an object type, name the pet through map selection |
| `nested-floor-revival` | Wait for a troll to revive from the inner sack of a container on the floor |
| `nested-revival` | Wait for a troll to revive from an inner sack in the hero’s pack |
| `options-unicode` | Use Enhanced1, change the rogue symbol set and run mode together, redraw and reopen options |
| `poly-abilities` | Gremlin, floating eye, mind flayer and giant spider abilities and restrictions |
| `potion-dip` | Uncurse and curse a sword with water, mix small potion stacks |
| `potion-stack` | Mix large magical, diluted and nonmagical stacks, including partial-stack results |
| `royal-jelly-hatch` | Rub royal jelly on a killer bee egg, cancel applying a second lump from a stack and wait for a queen bee to hatch |
| `shop-billing` | Enter via the public healer’s route, purchase unpaid banded mail and sell it back |
| `slime-expiry` | Eat a green slime glob and advance through the fatal timer and wizard survival |
| `slime-fire` | Burn away active sliming with a wand of fire and survive lethal damage in wizard mode |
| `status` | Save while blind, confused and hallucinating, restore, apply tools and take a combat turn |
| `stone-to-flesh` | Animate a newt statue on the floor and resolve the pet’s attack |
| `targeting` | Farlook help, monster/object/door cycling, target menu cancellation, fast cursor movement in travel targeting |
| `timed-potions` | Apply speed, levitation, sleep and full healing, including landing and waking up |
| `tools-corpses` | Tin a corpse, identify glass with a touchstone, apply a cream pie |
| `tools` | Apply a bag of tricks, horn of plenty, magic whistle, unicorn horn and towel |
| `traps` | Arm traps, disarm a land mine, animate a figurine and attempt pet and riding interactions |
| `undead-turning` | Revive a lichen and a newt from the floor, then probe downward |
| `wand-break` | Break charged and empty wands after wearing gauntlets of power |
| `wizcast` | Cast chain lightning and protection through the wizard spell menu |
| `writing` | Write known and unknown scrolls, charge a marker, read cursed armor magic and a cursed spellbook |

To re-record a recipe, run the upstream `scripts/record-session.mjs` against
a disposable native install with New York time and the release recording
epoch (`1777723200`). The native fixed-date parser inherits the live clock's
DST flag. The original captures pinned native `time()` to that epoch and used
a physical temporary install with the port's recording sysconf. Use an
installation where the native compressor can reopen the save descriptors.
Run both segments of each save and restore case in one recorder invocation.

To measure additional production JS execution, use the same source revision
for both runs.

```sh
node scripts/measure-recording-coverage.mjs sessions .cache/public-coverage.json
node scripts/measure-recording-coverage.mjs tests/recordings/native .cache/native-coverage.json .cache/public-coverage.json
```

V8 reports function entries and source block ranges for loaded scripts. The
comparison counts new function entries and exact matches to previously
zero-count block ranges. It cannot inventory every possible game state or
unloaded module. Exact native replay is the separate correctness check.
