/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 01:05:42 by abahja            #+#    #+#             */
/*   Updated: 2025/12/23 16:56:48 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "minilibx-linux/mlx.h"

void mlx_draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	
	// int dx = (x1 - x0);
	// int dy = (y1 - y0);
	// double distance = sqrt(dx * dx + dy * dy);
	// distance *= 3.3;
	// double d = distance;
	// printf("Distance: %f\n", distance);
	while (1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		// x0 += dx / distance;
		// y0 += dy / distance;
		// d--;
		if (x0 == x1 && y0 == y1)
			break;
		int err2 = err * 2;
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
void mlx_draw_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			mlx_pixel_put(mlx, win, x + j, y + i, color);
		}
	}
}
void mlx_draw_circle(void *mlx, void *win, int center_x, int center_y, int color)
{
	int radius = 3; // small radius for player representation
	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				mlx_pixel_put(mlx, win, center_x + x, center_y + y, color);
			}
		}
	}
}
void render_rays(t_config *cfg, void *mlx, void *win);
void cast_rays(t_config *cfg)
{
	int columnid = 0;
	double ray_angle = cfg->player.rot_angle - (FOV / 2);
	int num_rays = cfg->num_rays;
	printf("Casting %d rays\n", cfg->num_rays);
	// exit(1);
	while (columnid < cfg->num_rays)
	{
		// Normalize the angle
		// ray_angle = normalize_angle(ray_angle);

		// Set up ray
		t_ray *ray = &cfg->rays[columnid];
		ray->ray_angle = ray_angle;

		// Increment angle for next ray
		ray_angle += FOV / cfg->num_rays;
		columnid++;
	}
	render_rays(cfg, cfg->mlx, cfg->win);
}
void render_rays(t_config *cfg, void *mlx, void *win)
{
	int columnid = 0;
	while (columnid < cfg->num_rays)
	{
		t_ray *ray = &cfg->rays[columnid];
		// Scale to fit mini-map
		int ray_x = cfg->player.pos[X] * TILE_SIZE;
		int ray_y = cfg->player.pos[Y] * TILE_SIZE;
		printf("Ray %d: angle=%f\n", columnid, ray->ray_angle);
		int target_x = sin(ray->ray_angle) * 100;
		int target_y = cos(ray->ray_angle) * 100;

		// Draw the ray
		mlx_draw_line(mlx, win, ray_x, ray_y, ray_x + target_x, ray_y + target_y, 0xFFFF00);

		columnid++;
	}
}
void	render_scene(t_config *config)
{
	void	*mlx;
	void	*win;

	mlx = config->mlx;
	win = config->win;
	// mlx_clear_window(mlx, win);
		cast_rays(config);

	for (int i = 0; i < config->map.height && config->map.grid[i]; i++)
	{
		cast_rays(config);
		mlx_draw_circle(mlx, win, config->player.pos[X] * TILE_SIZE, config->player.pos[Y] * TILE_SIZE, 0xFF0000);
		// mlx_draw_line(mlx, win, config->player.pos[X] * TILE_SIZE, config->player.pos[Y] * TILE_SIZE, config->player.pos[X] * TILE_SIZE + (config->player.dir_view[X] * 50),
		// config->player.pos[Y] * TILE_SIZE + (config->player.dir_view[Y] * 50), 0x000000);
		for (int j = 0; j < config->map.width && config->map.grid[i][j]; j++)
		{
			if (config->map.grid[i][j] == '1')
				mlx_draw_rectangle(mlx, win, j * WINDOW_WIDTH, i * WINDOW_HEIGHT, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0x0000FF);
			else if (config->map.grid[i][j] == '0' || ft_strchr("NSEW", config->map.grid[i][j]))
				mlx_draw_rectangle(mlx, win, j * WINDOW_WIDTH, i * WINDOW_HEIGHT, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0xFFFFFF);
			else
				mlx_draw_rectangle(mlx, win, j * WINDOW_WIDTH, i * WINDOW_HEIGHT, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0x00000);
		}
		// cast_rays(config);
	}
	
}