# Dynamic window callback validation

Every row below resolves a current dynamic lookup site to the callback names exercised by the audit. Repeated sites in one helper remain separate audit entries. The two new shared metadata reads bring the original 40-site inventory to 42. Signatures are checked against the complete measured `window_procs` declaration.

| Location | Validated callback names |
| --- | --- |
| `js/nethack/apply.js:29` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_end_menu`, `win_start_menu` |
| `js/nethack/artifact.js:30` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putstr`, `win_start_menu` |
| `js/nethack/color-attributes.js:39` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_end_menu`, `win_start_menu` |
| `js/nethack/dig.js:30` | `win_delay_output`, `win_display_nhwindow` |
| `js/nethack/discoveries.js:14` | `win_clear_nhwindow`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putstr`, `win_start_menu`, `win_wait_synch` |
| `js/nethack/do-name.js:24` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_getlin`, `win_start_menu` |
| `js/nethack/end-lifecycle.js:20` | `win_clear_nhwindow`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_exit_nhwindows`, `win_mark_synch`, `win_outrip`, `win_putstr`, `win_raw_print`, `win_wait_synch` |
| `js/nethack/end-lifecycle.js:20` | `win_clear_nhwindow`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_exit_nhwindows`, `win_mark_synch`, `win_outrip`, `win_putstr`, `win_raw_print`, `win_wait_synch` |
| `js/nethack/end-lifecycle.js:40` | `win_clear_nhwindow`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_exit_nhwindows`, `win_mark_synch`, `win_outrip`, `win_putstr`, `win_raw_print`, `win_wait_synch` |
| `js/nethack/engrave.js:25` | `win_getlin` |
| `js/nethack/game-startup.js:21` | `win_askname`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_end_menu`, `win_putstr`, `win_start_menu` |
| `js/nethack/game-windows.js:41` | `win_create_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_start_menu` |
| `js/nethack/getpos.js:35` | `win_clear_nhwindow`, `win_cliparound`, `win_create_nhwindow`, `win_curs`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putstr`, `win_start_menu` |
| `js/nethack/hero-equipment.js:46` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_end_menu`, `win_start_menu` |
| `js/nethack/hero-equipment.js:46` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_end_menu`, `win_start_menu` |
| `js/nethack/insight.js:14` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putmixed`, `win_putstr`, `win_raw_print`, `win_start_menu` |
| `js/nethack/insight.js:28` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putmixed`, `win_putstr`, `win_raw_print`, `win_start_menu` |
| `js/nethack/light.js:26` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putstr` |
| `js/nethack/mail.js:30` | `win_delay_output`, `win_display_nhwindow` |
| `js/nethack/messages.js:59` | `win_display_nhwindow`, `win_putstr`, `win_raw_print` |
| `js/nethack/quest-pager.js:49` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putmsghistory`, `win_putstr` |
| `js/nethack/restore-lifecycle.js:26` | `win_add_menu`, `win_clear_nhwindow`, `win_cliparound`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putmsghistory`, `win_putstr`, `win_select_menu`, `win_start_menu`, `win_wait_synch` |
| `js/nethack/restore-lifecycle.js:28` | `win_add_menu`, `win_clear_nhwindow`, `win_cliparound`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putmsghistory`, `win_putstr`, `win_select_menu`, `win_start_menu`, `win_wait_synch` |
| `js/nethack/restore-lifecycle.js:46` | `win_add_menu`, `win_clear_nhwindow`, `win_cliparound`, `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putmsghistory`, `win_putstr`, `win_select_menu`, `win_start_menu`, `win_wait_synch` |
| `js/nethack/save-lifecycle.js:26` | `win_clear_nhwindow`, `win_display_nhwindow`, `win_exit_nhwindows`, `win_getmsghistory`, `win_mark_synch` |
| `js/nethack/save-lifecycle.js:29` | `win_clear_nhwindow`, `win_display_nhwindow`, `win_exit_nhwindows`, `win_getmsghistory`, `win_mark_synch` |
| `js/nethack/special-interactions.js:83` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putstr`, `win_start_menu` |
| `js/nethack/spell.js:32` | `win_clear_nhwindow`, `win_create_nhwindow`, `win_delay_output`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_start_menu` |
| `js/nethack/status.js:32` | `win_status_enablefield`, `win_status_finish`, `win_status_init`, `win_status_update` |
| `js/nethack/symbols.js:15` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_end_menu`, `win_preference_update`, `win_start_menu` |
| `js/nethack/teleport.js:40` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_start_menu` |
| `js/nethack/terminal-messages.js:43` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putstr` |
| `js/nethack/timeout-transport.js:15` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putstr` |
| `js/nethack/topten.js:15` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putstr`, `win_raw_print`, `win_raw_print_bold` |
| `js/nethack/topten.js:25` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putstr`, `win_raw_print`, `win_raw_print_bold` |
| `js/nethack/turn-loop.js:93` | `win_cliparound`, `win_create_nhwindow`, `win_display_file`, `win_display_nhwindow`, `win_end_menu`, `win_get_nh_event`, `win_start_menu` |
| `js/nethack/uhitm.js:21` | `win_delay_output`, `win_display_nhwindow` |
| `js/nethack/unix-terminal.js:44` | `win_exit_nhwindows`, `win_resume_nhwindows`, `win_suspend_nhwindows` |
| `js/nethack/version-info.js:25` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putstr`, `win_wait_synch` |
| `js/nethack/version-info.js:25` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_putstr`, `win_wait_synch` |
| `js/nethack/window-system.js:60` | `win_add_menu`, `win_askname`, `win_can_suspend`, `win_clear_nhwindow`, `win_cliparound`, `win_create_nhwindow`, `win_ctrl_nhwindow`, `win_curs`, `win_delay_output`, `win_destroy_nhwindow`, `win_display_file`, `win_display_nhwindow`, `win_doprev_message`, `win_end_menu`, `win_exit_nhwindows`, `win_get_ext_cmd`, `win_get_nh_event`, `win_getlin`, `win_getmsghistory`, `win_init_nhwindows`, `win_mark_synch`, `win_message_menu`, `win_nh_poskey`, `win_nhbell`, `win_nhgetch`, `win_number_pad`, `win_outrip`, `win_player_selection`, `win_preference_update`, `win_print_glyph`, `win_putmixed`, `win_putmsghistory`, `win_putstr`, `win_raw_print`, `win_raw_print_bold`, `win_resume_nhwindows`, `win_select_menu`, `win_start_menu`, `win_status_enablefield`, `win_status_finish`, `win_status_init`, `win_status_update`, `win_suspend_nhwindows`, `win_update_inventory`, `win_wait_synch`, `win_yn_function` |
| `js/nethack/wizcmds.js:27` | `win_create_nhwindow`, `win_destroy_nhwindow`, `win_display_nhwindow`, `win_end_menu`, `win_putstr`, `win_start_menu` |

There are 216 dispatcher cases and 34 actual lifecycle callback calls, including live callback replacement. Four negative checks reject a wrong signature, unknown name, unresolved caller and the previous restore metadata subset. This validates dispatch contracts, not every gameplay branch leading to them.

Detailed signatures, caller cases and source fingerprints: [dynamic-window-callbacks.json](dynamic-window-callbacks.json).
