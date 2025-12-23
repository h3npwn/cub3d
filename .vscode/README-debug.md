Debug example: BFS breakpoint

- Configuration: **Debug example: BFS breakpoint** (in the Run & Debug selector)
- What it does:
  - Builds the project (runs `make`) before launching.
  - Sources `.vscode/gdbinit` which sets a breakpoint at `bfs`, prints `map` dimensions and `copy[0]`, and displays `queue` on stops.
- How to use:
  1. Select **Debug example: BFS breakpoint** in the Run & Debug dropdown.
  2. Press **F5** to build and start debugging (it will stop at the breakpoint when reached).
  3. Use the Debug panel to inspect variables, the Call Stack, and modify watches.

Tips:
- Edit `.vscode/gdbinit` to add/remove breakpoints and display commands.
- Change the `args` in the launch configuration if you want a different map file.

Pretty-printers & visualization:
- A GDB pretty-printer script is provided at `.vscode/gdb_pretty_printers.py` and is auto-sourced by `.vscode/gdbinit`.
- The printers format `t_map` (shows width/height and grid rows), `char **` arrays (grid rows), and `t_node` linked lists.
- When debugging in VS Code (with the GDB-backed configuration), the **Variables** pane will display formatted values for these types. If you don't see the formatted view, check the Debug Console for the "gdb: cub3d pretty-printers loaded" message.

Test binary:
- Run `make test` to build the small test binary `cub3d_bfs_test`.
- Use the **Debug test: BFS main** configuration to debug it (select it in Run & Debug and press F5).
- This test sets up a tiny 3x3 map and runs `bfs` to exercise the BFS checker.
