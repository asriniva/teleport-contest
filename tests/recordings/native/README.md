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
and apply inputs. The `cloud-save-restore` save carries a stinking cloud into
subsequent movement and damage turns.

| Recording | Interactions |
| --- | --- |
| `altar-offerings` | Offer a white unicorn corpse and a lichen corpse to Thoth, then bless a potion on the altar through prayer |
| `artifacts` | Wear and invoke the Eye of the Aethiopica, wield and invoke Magicbane and Vorpal Blade |
| `bag-cancellation` | Put a cancellation wand into a bag of holding, handle the blast, potion prompt and wizard survival |
| `camera-mirror` | Aim a camera at the hero and the stairs, and aim a mirror at the hero and the ceiling |
| `cloud-save-restore` | Highlight jump and cloud targets, jump with boots, then save in a stinking cloud and take damage from it after restoring |
| `corpse-genders` | Revive explicitly male and female newt corpses, using a downward zap |
| `display-regex-collation` | Load message filters using a named space and a literal brace after repetition, then suppress the unknown-command message |
| `display-regex-dialect` | Exercise escaped letters in message and inventory color rules that the native C and SDK regex engines interpret differently |
| `floor-cancellation` | Cancel and recover a pile containing an enchanted sword, a potion of speed, a scroll of identify and a charged wand |
| `forced-lock` | Pry open a locked chest with a sword and trigger its trap when looting |
| `genocide-earth` | Genocide lichens, drop boulders with a scroll of earth, then read cursed fire magic |
| `grave-dig` | Dig out a grave, animate its owner, and resume interrupted digging in the pit |
| `hole-return` | Fall through a hole to level two, then revisit level one through wizard level teleport |
| `icebox-tip` | Put a troll corpse and food rations into an icebox, tip the contents into a carried sack, then empty that sack onto the floor |
| `inventory-reletter` | Split a dagger stack into an occupied letter, move the displaced stack, merge the daggers, then cancel another split |
| `levelchange-overflow` | Enter a signed overflow value in the experience-level prompt, then advance normally to level 2 |
| `lit-save-restore` | Light an oil lamp, candles, a potion of oil and a lantern, then save, restore, inspect inventory and switch off lights |
| `lock-container` | Lock and unlock a floor chest, split a potion stack into it, inspect and retrieve the potion, grease inventory |
| `melting-ice` | Step off ice that has a melt timer, then melt it with a bouncing bolt of fire |
| `menu-word-boundary` | Underline and color only whole-word “blessed” inventory entries |
| `message-equivalence` | Filter an unknown-command message using a single-character POSIX equivalence class |
| `message-word-boundary` | Hide an unknown-command message using native whole-word assertions |
| `mounted-lance` | Leash and saddle a pony, mount it, wield a cursed lance, target an empty square at reach, then dismount |
| `music` | Improvise with a flute, horn, bugle and harp, then play a drum of earthquake |
| `naming` | Name an individual object, call an object type, name the pet through map selection |
| `nested-floor-revival` | Wait for a troll to revive from the inner sack of a container on the floor |
| `nested-revival` | Wait for a troll to revive from an inner sack in the hero’s pack |
| `options-unicode` | Use Enhanced1, change the rogue symbol set and run mode together, redraw and reopen options |
| `petrify-eggs` | Cure a cockatrice egg's delayed petrification with a lizard corpse, then let the next egg's timer expire |
| `petrify-food` | Eat a cockatrice corpse from the floor, petrify immediately and decline death in wizard mode |
| `poly-abilities` | Gremlin, floating eye, mind flayer and giant spider abilities and restrictions |
| `polymorph-trap` | Trigger a polymorph trap with polymorph control, become a xorn and move through solid rock |
| `potion-dip` | Uncurse and curse a sword with water, mix small potion stacks |
| `potion-stack` | Mix large magical, diluted and nonmagical stacks, including partial-stack results |
| `prompt-combo` | Open combined message recall with repeated control-P, then return to a quit confirmation |
| `prompt-history` | Open full message history after using inventory and during a prayer confirmation, then backspace and cancel two line prompts |
| `prompt-reversed` | Open reversed message history, return to a quit confirmation, wrap an annotation prompt to a second row and erase the line |
| `prompt-single` | Recall individual messages inside a prayer prompt, then edit a level name with backspace and line erase |
| `redraw-enhanced-symbols` | Redraw with Enhanced1 after magic mapping and while hallucinating |
| `redraw-engulfed` | Redraw and open inventory while swallowed by a purple worm |
| `redraw-invisible` | Make a lichen invisible, attack it and redraw, then redraw while blind, change the travel target filter and open a target menu |
| `redraw-water` | Enter a pool wearing an amulet of magical breathing, redraw and open inventory underwater, then climb out |
| `remove-armor` | Destroy a worn cloak with a scroll, unwield the weapon through take-off-all, then remove a helmet, boots and body armor through the same command |
| `royal-jelly-hatch` | Rub royal jelly on a killer bee egg, cancel applying a second lump from a stack and wait for a queen bee to hatch |
| `shop-billing` | Enter via the public healer’s route, purchase unpaid banded mail and sell it back |
| `sink-rings` | Drop three rings into a sink, recover a ring previously dropped, then fall when a ring of levitation is put on over the sink |
| `slime-expiry` | Eat a green slime glob and advance through the fatal timer and wizard survival |
| `slime-fire` | Burn away active sliming with a wand of fire and survive lethal damage in wizard mode |
| `status` | Save while blind, confused and hallucinating, restore, apply tools and take a combat turn |
| `status-hilites` | Exercise three-line weapon and armor status, HP and ability changes, blindness and levitation colors, and a timed gold highlight that expires |
| `stone-to-flesh` | Animate a newt statue on the floor and resolve the pet’s attack |
| `targeting` | Farlook help, monster/object/door cycling, target menu cancellation, fast cursor movement in travel targeting |
| `timed-potions` | Apply speed, levitation, sleep and full healing, including landing and waking up |
| `tools-corpses` | Tin a corpse, identify glass with a touchstone, apply a cream pie |
| `tools` | Apply a bag of tricks, horn of plenty, magic whistle, unicorn horn and towel |
| `trailing-path` | Ask the wizard Lua loader to open a regular file with a trailing slash, dismiss the error and redraw |
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
