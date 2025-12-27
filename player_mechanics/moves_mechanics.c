/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_mechanics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:24:25 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 18:36:08 by abahja           ###   ########.fr       */
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

void	move_forward(t_cub3d *cub3d)
{
	cub3d->player.posx += cub3d->player.dir_x * M_SPEED;
	cub3d->player.posy += cub3d->player.dir_y * M_SPEED;
}

void	move_backward(t_cub3d *cub3d)
{
	cub3d->player.posx -= cub3d->player.dir_x * M_SPEED;
	cub3d->player.posy -= cub3d->player.dir_y * M_SPEED;
}

void	strafe_left(t_cub3d *cub3d)
{
	cub3d->player.posx -= cub3d->player.plane_x * M_SPEED;
	cub3d->player.posy -= cub3d->player.plane_y * M_SPEED;
}

void	strafe_right(t_cub3d *cub3d)
{
	cub3d->player.posx += cub3d->player.plane_x * M_SPEED;
	cub3d->player.posy += cub3d->player.plane_y * M_SPEED;
}
