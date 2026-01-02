/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_mechanics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:24:25 by abahja            #+#    #+#             */
/*   Updated: 2026/01/02 22:23:45 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_rotation(t_cub3d *cub3d, double angle)
{
	double	x;

	x = cub3d->player.dir[X];
	cub3d->player.dir[X] = x * cos(angle) - cub3d->player.dir[Y] * sin(angle);
	cub3d->player.dir[Y] = x * sin(angle) + cub3d->player.dir[Y] * cos(angle);
	x = cub3d->player.plane[X];
	cub3d->player.plane[X] = x * cos(angle)
		- cub3d->player.plane[Y] * sin(angle);
	cub3d->player.plane[Y] = x * sin(angle)
		+ cub3d->player.plane[Y] * cos(angle);
}

void	move(t_cub3d *cub3d, double x, double y)
{
	double	nx;
	double	ny;

	nx = cub3d->player.pos[X] + x * M_SPEED;
	ny = cub3d->player.pos[Y] + y * M_SPEED;
	if (cub3d->map.grid[(int)(cub3d->player.pos[Y])][(int)(nx)] != '1')
		cub3d->player.pos[X] = nx;
	if (cub3d->map.grid[(int)(ny)][(int)(cub3d->player.pos[X])] != '1')
		cub3d->player.pos[Y] = ny;
}
