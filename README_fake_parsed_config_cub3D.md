# cub3D — Temporary Fake Parsed Configuration

This document provides a **temporary, hard-coded parsed configuration** so that the
**engine / MLX / raycasting part** of cub3D can be developed **without waiting for the parser**.

This setup strictly follows the **parsing contract** and the **cub3D subject (v11.0)**.

---

## 🎯 Purpose

- Allow engine development independently of parsing
- Simulate a fully valid parsed `.cub` file
- Replaceable later with `parse_cub()` without refactoring

---

## 🧱 Fake Parsed `t_config`

```c
t_config *fake_config(void)
{
    t_config *cfg;

    cfg = malloc(sizeof(t_config));
    if (!cfg)
        return (NULL);

    /* TEXTURE PATHS */
    cfg->tex.north = ft_strdup("assets/north.xpm");
    cfg->tex.south = ft_strdup("assets/south.xpm");
    cfg->tex.west  = ft_strdup("assets/west.xpm");
    cfg->tex.east  = ft_strdup("assets/east.xpm");

    /* FLOOR COLOR */
    cfg->floor.r = 50;
    cfg->floor.g = 50;
    cfg->floor.b = 50;
    cfg->floor.value = (50 << 16 | 50 << 8 | 50);

    /* CEILING COLOR */
    cfg->ceiling.r = 150;
    cfg->ceiling.g = 150;
    cfg->ceiling.b = 150;
    cfg->ceiling.value = (150 << 16 | 150 << 8 | 150);

    /* MAP */
    cfg->map.height = 7;
    cfg->map.width = 9;

    cfg->map.grid = malloc(sizeof(char *) * cfg->map.height);
    cfg->map.grid[0] = ft_strdup("111111111");
    cfg->map.grid[1] = ft_strdup("100000001");
    cfg->map.grid[2] = ft_strdup("101111101");
    cfg->map.grid[3] = ft_strdup("100000001");
    cfg->map.grid[4] = ft_strdup("101011101");
    cfg->map.grid[5] = ft_strdup("100000001");
    cfg->map.grid[6] = ft_strdup("111111111");

    /* PLAYER */
    cfg->player.x = 4.5;
    cfg->player.y = 3.5;
    cfg->player.dir = 'N';

    return (cfg);
}
```

### Map Visualization

```
111111111
100000001
101111101
1000P0001
101011101
100000001
111111111
```

`P` = player start (center of cell, facing North)

---

## 🧭 Player Direction Initialization

```c
void init_player_direction(t_game *g)
{
    if (g->cfg->player.dir == 'N')
    {
        g->dir_x = 0;
        g->dir_y = -1;
        g->plane_x = 0.66;
        g->plane_y = 0;
    }
    else if (g->cfg->player.dir == 'S')
    {
        g->dir_x = 0;
        g->dir_y = 1;
        g->plane_x = -0.66;
        g->plane_y = 0;
    }
    else if (g->cfg->player.dir == 'E')
    {
        g->dir_x = 1;
        g->dir_y = 0;
        g->plane_x = 0;
        g->plane_y = 0.66;
    }
    else if (g->cfg->player.dir == 'W')
    {
        g->dir_x = -1;
        g->dir_y = 0;
        g->plane_x = 0;
        g->plane_y = -0.66;
    }
}
```

This matches classic Wolfenstein 3D raycasting math and is fully subject-compliant.

---

## ▶️ Temporary Usage in `main.c`

```c
int main(void)
{
    t_game game;

    game.cfg = fake_config();
    if (!game.cfg)
        return (1);

    init_mlx(&game);
    init_player_direction(&game);
    game_loop(&game);
}
```

Later, simply replace:

```c
game.cfg = fake_config();
```

with:

```c
game.cfg = parse_cub(argv[1]);
```

No other changes are required.

---

## 🧪 Recommended Practice

Place this file in:
```
src/debug/fake_config.c
```

And guard it:

```c
#ifdef DEBUG
    cfg = fake_config();
#else
    cfg = parse_cub(argv[1]);
#endif
```

---

## ✅ What You Can Implement With This

- MLX initialization
- Frame buffer
- Raycasting (DDA)
- Wall rendering
- Texture sampling
- Player movement & rotation
- Collision handling
- Proper exit handling

---

## 📌 Notes

- This file is **temporary**
- Must be removed or disabled before final submission
- Perfect for parallel team development
