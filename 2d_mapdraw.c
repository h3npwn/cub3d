/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_mapdraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:22:27 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 18:30:54 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/cub3d.h"

void	draw_map2d(t_cub3d *cub3d)
{
	int		y;
	int		x;
	int		tile;
	char	cell;
	int		color;

	tile = TILE_SIZE;
	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (cub3d->map.grid[y][x])
		{
			cell = cub3d->map.grid[y][x];
			color = (cell == '1') ? DARK_GRAY : BLACK;
			draw_rectangle(&cub3d->img_frame, x * tile, y * tile, tile, tile, color);
			x++;
		}
		y++;
	}
	draw_circle(&cub3d->img_frame,
		(int)(cub3d->player.posx * tile),
		(int)(cub3d->player.posy * tile),
		RED);
	draw_line(&cub3d->img_frame,
		(int)(cub3d->player.posx * tile),
		(int)(cub3d->player.posy * tile),
		(int)((cub3d->player.posx + cub3d->player.dir_x * 0.8) * tile),
		(int)((cub3d->player.posy + cub3d->player.dir_y * 0.8) * tile),
		YELLOW);
}