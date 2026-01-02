/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:27:27 by abahja            #+#    #+#             */
/*   Updated: 2026/01/02 22:06:00 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	destroy_exit(t_cub3d *cub3d)
{
	mlx_destroy_all(cub3d);
	heap_manager(0, 'f', 0);
	exit(0);
	return (0);
}

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
