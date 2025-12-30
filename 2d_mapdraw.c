/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_mapdraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:22:27 by abahja            #+#    #+#             */
/*   Updated: 2025/12/30 14:22:31 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/cub3d.h"

void	draw_map2d(t_cub3d *cub3d)
{
	int		y;
	int		x;
	char	cell;
	int		color;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (cub3d->map.grid[y][x])
		{
			cell = cub3d->map.grid[y][x];
			if (cell == '1')
				color = DARK_GRAY;
			else if (cell == '0')
				color = LIGHT_GRAY;
			else
				color = BLACK;
			draw_rectangle(&cub3d->img_frame, x * (TILE_SIZE), y * (TILE_SIZE), color);
			x++;
		}
		y++;
	}
	draw_circle(&cub3d->img_frame, (int)(cub3d->player.posx * TILE_SIZE),
		(int)(cub3d->player.posy * TILE_SIZE), RED);
	draw_line(&cub3d->img_frame,
		(int)(cub3d->player.posx * TILE_SIZE),
		(int)(cub3d->player.posy * TILE_SIZE),
		(int)((cub3d->player.posx + cub3d->player.dir_x * 1.0) * TILE_SIZE),
		(int)((cub3d->player.posy + cub3d->player.dir_y * 1.0) * TILE_SIZE),
		YELLOW);
}
