
#include "includes/cub3d.h"

static void	ft_setdirs_ew(t_cub3d *cfg)
{
	double plane;
	
	plane = 0.66;
	if (cfg->initial_dir == 'E')
	{
		cfg->player.dir_x = 1;
		cfg->player.dir_y = 0;
		cfg->player.plane_x = 0;
		cfg->player.plane_y = plane;
	}
	else if (cfg->initial_dir == 'W')
	{
		cfg->player.dir_x = -1;
		cfg->player.dir_y = 0;
		cfg->player.plane_x = 0;
		cfg->player.plane_y = -plane;
	}
}
static void	ft_setdirs_ns(t_cub3d *cfg)
{
	double plane;
	
	plane = 0.66;
	if (cfg->initial_dir == 'N')
	{
		cfg->player.dir_x = 0;
		cfg->player.dir_y = -1;
		cfg->player.plane_x = plane;
		cfg->player.plane_y = 0;
	}
	else if (cfg->initial_dir == 'S')
	{ 
		cfg->player.dir_x = 0;
		cfg->player.dir_y = 1;
		cfg->player.plane_x = -plane;
		cfg->player.plane_y = 0;
	}
}
void	set_directions(t_cub3d *cfg)
{
	ft_setdirs_ew(cfg);
	ft_setdirs_ns(cfg);
}