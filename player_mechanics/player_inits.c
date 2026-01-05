/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:30:03 by abahja            #+#    #+#             */
/*   Updated: 2026/01/05 01:48:45 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_setdirs_ew(t_cub3d *cfg)
{
	double	plane;

	plane = tan((FOV * M_PI / 360.0));
	cfg->player.dir[Y] = 0;
	cfg->player.plane[X] = 0;
	if (cfg->initial_dir == 'E')
	{
		cfg->player.dir[X] = 1;
		cfg->player.plane[Y] = plane;
	}
	else if (cfg->initial_dir == 'W')
	{
		cfg->player.dir[X] = -1;
		cfg->player.plane[Y] = -plane;
	}
}

static void	ft_setdirs_ns(t_cub3d *cfg)
{
	double	plane;

	plane = tan((FOV * M_PI / 360.0));
	cfg->player.dir[X] = 0;
	cfg->player.plane[Y] = 0;
	if (cfg->initial_dir == 'N')
	{
		cfg->player.dir[Y] = -1;
		cfg->player.plane[X] = plane;
	}
	else if (cfg->initial_dir == 'S')
	{
		cfg->player.dir[Y] = 1;
		cfg->player.plane[X] = -plane;
	}
}

void	set_directions(t_cub3d *cfg)
{
	ft_setdirs_ew(cfg);
	ft_setdirs_ns(cfg);
}
