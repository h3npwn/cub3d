/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:27:27 by abahja            #+#    #+#             */
/*   Updated: 2026/01/05 04:16:51 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int key, t_cub3d *cub3d)
{
	t_movements	*moves;

	moves = &cub3d->moves;
	if (key == ESC)
		destroy_exit(cub3d);
	if (key == MOVE_UP)
		moves->m_up = 1;
	if (key == MOVE_DOWN)
		moves->m_down = 1;
	if (key == MOVE_LEFT)
		moves->m_left = 1;
	if (key == MOVE_RIGHT)
		moves->m_right = 1;
	if (key == LEFT_ARROW)
		moves->c_left = 1;
	if (key == RIGHT_ARROW)
		moves->c_right = 1;
	return (0);
}

int	key_release(int key, t_cub3d *cub3d)
{
	t_movements	*moves;

	moves = &cub3d->moves;
	if (key == MOVE_UP)
		moves->m_up = 0;
	if (key == MOVE_DOWN)
		moves->m_down = 0;
	if (key == MOVE_LEFT)
		moves->m_left = 0;
	if (key == MOVE_RIGHT)
		moves->m_right = 0;
	if (key == LEFT_ARROW)
		moves->c_left = 0;
	if (key == RIGHT_ARROW)
		moves->c_right = 0;
	return (0);
}

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

void	apply_movements(t_cub3d *cub3d)
{
	if (cub3d->moves.m_up)
		move(cub3d, cub3d->player.dir[X], cub3d->player.dir[Y]);
	if (cub3d->moves.m_down)
		move(cub3d, -cub3d->player.dir[X], -cub3d->player.dir[Y]);
	if (cub3d->moves.m_right)
		move(cub3d, cub3d->player.plane[X], cub3d->player.plane[Y]);
	if (cub3d->moves.m_left)
		move(cub3d, -cub3d->player.plane[X], -cub3d->player.plane[Y]);
	if (cub3d->moves.c_left)
		player_rotation(cub3d, -R_SPEED);
	if (cub3d->moves.c_right)
		player_rotation(cub3d, R_SPEED);
}
