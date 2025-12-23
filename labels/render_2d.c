/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 01:05:42 by abahja            #+#    #+#             */
/*   Updated: 2025/12/23 20:03:07 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <mlx.h>

static void	draw_minimap(t_config *cfg);
static void	draw_player(t_config *cfg);
static void	draw_rays(t_config *cfg);
static void	trace_ray(t_config *cfg, t_ray *ray);
static int	is_wall_cell(t_config *cfg, int x, int y);





static int	is_wall_cell(t_config *cfg, int x, int y)
{
	int	row_len;

	if (y < 0 || y >= cfg->map.height || x < 0 || !cfg->map.grid[y])
		return (1);
	row_len = ft_strlen(cfg->map.grid[y]);
	if (x >= row_len || cfg->map.grid[y][x] == '\0')
		return (1);
	return (cfg->map.grid[y][x] == '1');
}

static void	trace_ray(t_config *cfg, t_ray *ray)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	ray_dir_x = cos(ray->ray_angle);
	ray_dir_y = sin(ray->ray_angle);
	map_x = (int)cfg->player->pos[X];
	map_y = (int)cfg->player->pos[Y];
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
	step_x = (ray_dir_x < 0) ? -1 : 1;
	step_y = (ray_dir_y < 0) ? -1 : 1;
	if (ray_dir_x < 0)
		side_dist_x = (cfg->player->pos[X] - map_x) * delta_dist_x;
	else
		side_dist_x = (map_x + 1.0 - cfg->player->pos[X]) * delta_dist_x;
	if (ray_dir_y < 0)
		side_dist_y = (cfg->player->pos[Y] - map_y) * delta_dist_y;
	else
		side_dist_y = (map_y + 1.0 - cfg->player->pos[Y]) * delta_dist_y;
	hit = 0;
	side = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (is_wall_cell(cfg, map_x, map_y))
			hit = 1;
	}
	if (side == 0)
		ray->distance = (map_x - cfg->player->pos[X] + (1 - step_x) / 2.0) / (ray_dir_x == 0 ? 1e-6 : ray_dir_x);
	else
		ray->distance = (map_y - cfg->player->pos[Y] + (1 - step_y) / 2.0) / (ray_dir_y == 0 ? 1e-6 : ray_dir_y);
	if (ray->distance < 0)
		ray->distance = 0;
	ray->wall_hit_x = cfg->player->pos[X] + ray_dir_x * ray->distance;
	ray->wall_hit_y = cfg->player->pos[Y] + ray_dir_y * ray->distance;
}

void	cast_rays(t_config *cfg)
{
	int		i;
	double	ray_angle;
	double	step;

	if (!cfg->rays || cfg->num_rays <= 0)
		return ;
	ray_angle = cfg->player->rot_angle - (FOV / 2.0);
	step = FOV / cfg->num_rays;
	i = 0;
	while (i < cfg->num_rays)
	{
		cfg->rays[i].ray_angle = normalize_angle(ray_angle);
		trace_ray(cfg, &cfg->rays[i]);
		ray_angle += step;
		i++;
	}
}

static void	draw_minimap(t_config *cfg)
{
	int	i;
	int	j;
	char	cell;

	i = 0;
	while (i < cfg->map.height && cfg->map.grid[i])
	{
		j = 0;
		while (j < cfg->map.width && cfg->map.grid[i][j])
		{
			cell = cfg->map.grid[i][j];
			if (cell == '1')
				mlx_draw_rectangle(cfg->mlx, cfg->win, j * WINDOW_WIDTH, i * WINDOW_HEIGHT, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0x0000FF);
			else if (cell == '0' || ft_strchr("NSEW", cell))
				mlx_draw_rectangle(cfg->mlx, cfg->win, j * WINDOW_WIDTH, i * WINDOW_HEIGHT, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_config *cfg)
{
	mlx_draw_circle(cfg->mlx, cfg->win, cfg->player->pos[X] * TILE_SIZE,
		cfg->player->pos[Y] * TILE_SIZE, 0xFF0000);
}

static void	draw_rays(t_config *cfg)
{
	int	i;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	if (!cfg->rays)
		return ;
	start_x = cfg->player->pos[X] * TILE_SIZE;
	start_y = cfg->player->pos[Y] * TILE_SIZE;
	i = 0;
	while (i < cfg->num_rays)
	{
		end_x = cfg->rays[i].wall_hit_x * TILE_SIZE;
		end_y = cfg->rays[i].wall_hit_y * TILE_SIZE;
		mlx_draw_line(cfg->mlx, cfg->win, start_x, start_y, end_x, end_y, 0xFFFF00);
		i++;
	}
}

void	render_scene(t_config *config)
{
	if (!config || !config->mlx || !config->win)
		return ;
	// mlx_clear_window(config->mlx, config->win);
	draw_minimap(config);
	draw_player(config);
	cast_rays(config);
	draw_rays(config);
}
