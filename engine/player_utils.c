#include "../headers/cub3d.h"

void	player_set_angle(t_config *config, double angle)
{
	t_player	*player;

	player = &config->player;
	player->rot_angle = normalize_angle(angle);
}

void	player_locate_spawn(t_config *config)
{
	int		y;
	int		x;
	char	c;

	if (!config || !config->map.grid)
		return ;
	y = 0;
	while (y < config->map.height && config->map.grid[y])
	{
		x = 0;
		while (config->map.grid[y][x])
		{
			c = config->map.grid[y][x];
			if (ft_strchr("NSEW", c))
			{
				config->player.pos[X] = x;
				config->player.pos[Y] = y;
				config->player.dir = c;
				return ;
			}
			x++;
		}
		y++;
	}
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
	return (0.0);
}

void	player_view_init(t_config *config)
{
	player_locate_spawn(config);
	config->player.pos[X] += 0.5;
	config->player.pos[Y] += 0.5;
	player_set_angle(config, dir_to_angle(config->player.dir));
}
