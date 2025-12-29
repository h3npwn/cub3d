#include "includes/cub3d.h"
#include "includes/types.h"
#include <stdlib.h>
#include <mlx.h>

/*
** ======================================
** DRAW CIRCLE (BUFFERED)
** ======================================
*/

void	draw_circle(t_img_frame *img, int center_x, int center_y, int color)
{
	int	radius;
	int	x;
	int	y;

	radius = 3;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				img_pixel_put(img, center_x + x, center_y + y, color);
			x++;
		}
		y++;
	}
}

/*
** ======================================
** DRAW RECTANGLE (BUFFERED)
** ======================================
*/

void	draw_rectangle(t_img_frame *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			img_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/*
** ======================================
** DRAW LINE (BUFFERED - BRESENHAM)
** ======================================
*/

void	draw_line(t_img_frame *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx,dy,sx,sy,err,err2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		if (x0 == x1 && y0 == y1)
			break ;
		img_pixel_put(img, x0, y0, color);
		err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
