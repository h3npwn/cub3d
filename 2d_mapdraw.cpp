/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_mapdraw.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:22:27 by abahja            #+#    #+#             */
/*   Updated: 2026/01/02 22:39:15 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/cub3d.h"

// void	draw_map2d(t_cub3d *cub3d)
// {
// 	int		y;
// 	int		x;
// 	char	cell;
// 	int		color;

// 	y = 0;
// 	while (y < cub3d->map.height)
// 	{
// 		x = 0;
// 		while (cub3d->map.grid[y][x])
// 		{
// 			cell = cub3d->map.grid[y][x];
// 			if (cell == '1')
// 				color = DARK_GRAY;
// 			else if (cell == '0')
// 				color = LIGHT_GRAY;
// 			else
// 				color = BLACK;
// 			draw_rectangle(&cub3d->img_frame, x * (TILE_SIZE), y * (TILE_SIZE), color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_circle(&cub3d->img_frame, (int)(cub3d->player.pos[X] * TILE_SIZE),
// 		(int)(cub3d->player.pos[Y] * TILE_SIZE), RED);
// 	draw_line(&cub3d->img_frame,
// 		(int)(cub3d->player.pos[X] * TILE_SIZE),
// 		(int)(cub3d->player.pos[Y] * TILE_SIZE),
// 		(int)((cub3d->player.pos[X] + cub3d->player.dir[X] * 1.0) * TILE_SIZE),
// 		(int)((cub3d->player.pos[Y] + cub3d->player.dir[Y] * 1.0) * TILE_SIZE),
// 		YELLOW);
// }
