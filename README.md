# cub3D — Subject Reference

This README captures the essential context from the official cub3D v11.0 subject
so the whole team can work without reopening the PDF.

---

## Foreword & Goals

- Inspired by *Wolfenstein 3D* (1992) and its successors (*Doom*, *Quake*), the
  project revisits classic ray-casting to render a maze from a first-person view.
- Objectives: keep writing rigorous C, respect the Norm, handle colors, windows,
  events, and discover how math supports efficient rendering algorithms.
- Suggested: play the original Wolfenstein (http://users.atw.hu/wolf3d/) for
  context before coding.

---

## Common Instructions

- Language: **C** only, Norm-compliant, using `cc` with `-Wall -Wextra -Werror`.
- Stable behavior is mandatory: no leaks, crashes, or UB outside undefined cases.
- Heap allocations must be freed; tests are encouraged for defenses.
- Submit `Makefile` with rules `all`, `clean`, `fclean`, `re`, `bonus`. Avoid
  unnecessary relinks.
- If bonuses exist, provide a `bonus` rule and put their code into `_bonus.c/h`
  files unless stated otherwise.
- `libft` is authorized but must live in `./libft/` with its own Makefile.
- Only the Git repository at evaluation time is graded; Deepthought runs after
  peer-evals.

---

## AI Usage Guidelines

- Use AI for repetitive work, better prompts, and productivity, but always review,
  test, and understand generated code. Assume responsibility for any AI-assisted
  content.
- Develop prompting skills, study AI limitations/biases, and favor peer feedback
  to catch blind spots.
- Good practice: brainstorm with AI, then validate/refine with peers. Bad
  practice: copy AI code you cannot explain—this fails the defense.

---

## Mandatory Program Requirements

| Item              | Requirement |
|-------------------|-------------|
| Program name      | `cub3D` |
| Arguments         | `./cub3D <scene.cub>` |
| External functions| `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, `gettimeofday`, all math functions (`-lm`), all MiniLibX |
| Libft             | Allowed |

Core expectations:
- Render a “realistic” 3D view of a maze via ray-casting inside a MiniLibX window.
- Window interactions (focus changes, minimize, close) must remain smooth.
- Display different wall textures depending on orientation (North/South/West/East).
- Floor and ceiling colors must be configurable independently.
- Controls (must be responsive and produce clean shutdowns):
  - `W/A/S/D` move the player->
  - Left/right arrows rotate the camera.
  - `ESC` or closing the window must exit cleanly.

---

## `.cub` Scene File Specification

- First argument to the program; parsing errors must print `Error\n<message>`.
- Valid characters in the map: `0` = empty, `1` = wall, `N/S/E/W` = player start
  + orientation (exactly one spawn expected).
- Map must be enclosed by walls; spaces are valid map cells and must be handled.
- File sections may include blank lines; ordering is free except the map must
  come last. Each property begins with its identifier:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F  220,100,0    # floor color in [0,255]
C  225,30,0     # ceiling color in [0,255]
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

---

## Build & Execution

```bash
make            # builds cub3D with MiniLibX + libft
./cub3D map.cub # runs the engine with a scene
```

---

## Error Handling

Any misconfiguration must terminate gracefully:

```
Error
Detailed message explaining what failed
```

Ensure allocations, file descriptors, and MLX resources are cleaned before exit.

---

## Bonus Features (only graded if mandatory part scores full points)

- Wall collisions.
- Minimap rendering.
- Doors with open/close logic.
- Animated sprites.
- Mouse look rotation.

Other format tweaks or map symbols are allowed for bonuses if justified during
the defense.

---

## Submission & Peer Evaluation

- Double-check repository filenames before pushing; only committed work counts.
- During peer-eval a small live modification may be requested to prove mastery.
- Be ready to adjust a function, display, or data structure quickly using your
  normal setup.

---

## Quick Reference Checklist

- [ ] Norm-compliant C, Makefile with required rules and flags.
- [ ] `libft` vendored; MiniLibX linked; math library linked (`-lm`).
- [ ] `.cub` parser handles textures, colors, map ordering, spaces, and validation.
- [ ] Ray-casting engine renders textured walls, painted floor/ceiling, player
      moves/rotates per controls, smooth window lifecycle.
- [ ] Clean shutdown paths for ESC, window close, or parsing errors.
- [ ] Optional bonuses gated behind a perfect mandatory implementation.
