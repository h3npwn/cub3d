/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_mechanics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:24:25 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 22:12:13 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_rotation(t_cub3d *cub3d, double angle)
{
	double	x;

	x = cub3d->player.dir_x;
	cub3d->player.dir_x = x * cos(angle) - cub3d->player.dir_y * sin(angle);
	cub3d->player.dir_y = x * sin(angle) + cub3d->player.dir_y * cos(angle);
	x = cub3d->player.plane_x;
	cub3d->player.plane_x = x * cos(angle) - cub3d->player.plane_y * sin(angle);
	cub3d->player.plane_y = x * sin(angle) + cub3d->player.plane_y * cos(angle);
}

void	move(t_cub3d *cub3d, double x, double y)
{
	double	nx;
	double	ny;

	nx = cub3d->player.posx + x * M_SPEED;
	ny = cub3d->player.posy + y * M_SPEED;
	if (cub3d->map.grid[(int)(cub3d->player.posy)][(int)(nx)] != '1')
		cub3d->player.posx = nx;
	if (cub3d->map.grid[(int)(ny)][(int)(cub3d->player.posx)] != '1')
		cub3d->player.posy = ny;

}
