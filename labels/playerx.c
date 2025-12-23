#include "../headers/cub3d.h"
#include <mlx.h>
#include <math.h>
#include <sys/types.h>

double	normalize_angle(double angle)
{
	const double	two_pi = 2.0 * M_PI;

	while (angle < 0)
		angle += two_pi;
	while (angle >= two_pi)
		angle -= two_pi;
	return (angle);
}

static double	dir_to_angle(char dir)
{
	if (dir == 'N')
		return (-M_PI / 2.0);
	if (dir == 'S')
		return (M_PI / 2.0);
	if (dir == 'E')
		return (0.0);
	if (dir == 'W')
		return (M_PI);
	return (-M_PI / 2.0);
}

void	player_set_angle(t_config *config, double angle)
{
	t_player	*player;

	player = &config->player;
	player->rot_angle = normalize_angle(angle);
	player->dir_view[0] = cos(player->rot_angle);
	player->dir_view[1] = sin(player->rot_angle);
	player->plane[0] = -player->dir_view[1] * 0.66;
	player->plane[1] = player->dir_view[0] * 0.66;
}

void	player_view_init(t_config *config)
{
	player_set_angle(config, dir_to_angle(config->player->dir));
}


