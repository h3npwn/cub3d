#include "../headers/cub3d.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <sys/types.h>



static void player_view_init(t_config *config)
{
	static const struct {
		char dir;
		double dx, dy;
		double px, py;
	} dir_map[] = {
		{'N', 0.0, -1.0,  0.66,  0.0},
		{'S', 0.0,  1.0, -0.66,  0.0},
		{'E', 1.0,  0.0,  0.0,   0.66},
		{'W',-1.0,  0.0,  0.0,  -0.66},
		{0,   0.0,  0.0,  0.0,   0.0}
	};
	for (int i = 0; dir_map[i].dir; ++i)
	{
		if (config->player.dir == dir_map[i].dir)
		{
			config->player.dir_view[0] = dir_map[i].dx;
			config->player.dir_view[1] = dir_map[i].dy;
			config->player.plane[0] = dir_map[i].px;
			config->player.plane[1] = dir_map[i].py;
			return;
		}
	}
	config->player.dir_view[0] = 0.0;
	config->player.dir_view[1] = -1.0;
	config->player.plane[0] = 0.66;
	config->player.plane[1] = 0.0;
}

void player_inits(t_cub *cub)
{
    t_config *cfg = cub->cfg;
    t_player *player = &cfg->player;

    player_view_init(cfg);
    player->move_speed = 3.0;
    player->rot_speed = 3 * (M_PI / 180); // 3 degrees in radians
    player->radius = 0.2;
    player->walk_direction = 0;
    player->turn_direction = 0;
    player->rot_angle = M_PI / 2; // Facing upward initially
}