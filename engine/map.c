/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:09 by abahja            #+#    #+#             */
/*   Updated: 2025/12/23 23:05:50 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	is_wall_cell(t_map *map, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	return (grid_y < 0 || grid_y >= map->height || grid_x < 0
		|| grid_x >= (int)ft_strlen(map->grid[grid_y])
		|| map->grid[grid_y][grid_x] == '1');
}

static void	draw_tiles(t_cub *cub)
{
	int		i;
	int		j;
	t_map	*map;

	map = &cub->cfg->map;
	i = 0;
	while (i < map->height && map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			draw_rectangle(&cub->frame, j *( TILE_SIZE - 20), i *( TILE_SIZE - 20),
			(	TILE_SIZE - 20),( TILE_SIZE - 20), map->grid[i][j] == '1' ? DARK_GRAY : WHITE);
			j++;
		}
		i++;
	}
}

static void	draw_single_ray(t_cub *cub, double angle)
{
	t_player	*player;
	double		dist;
	double		hit_x;
	double		hit_y;
	double		max_dist;

	player = &cub->cfg->player;
	dist = 0.0;
	max_dist = fmax(cub->cfg->map.width, cub->cfg->map.height) * 1.5;
    int rot_angel = cub->cfg->player.rot_angle * (180.0 / M_PI);
	while (dist < max_dist)
	{
		hit_x = player->pos[X] + cos(angle) * dist;
		hit_y = player->pos[Y] + sin(angle) * dist;
		if (is_wall_cell(&cub->cfg->map, hit_x, hit_y))
			break ;
		dist += 0.01;
	}
	draw_line(&cub->frame, player->pos[X] * (TILE_SIZE - 20), player->pos[Y] * (TILE_SIZE - 20),
		hit_x * (TILE_SIZE - 20), hit_y * (TILE_SIZE - 20), YELLOW);
}

static void	draw_rays(t_cub *cub)
{
	int		i;
	int		rays;
	double	angle;
	double	step;

	rays = 30;
	angle = cub->cfg->player.rot_angle - (FOV / 2);
	step = FOV / (double)(rays - 1);
	i = 0;
	while (i < rays)
	{
		draw_single_ray(cub, normalize_angle(angle));
		angle += step;
		i++;
	}
}

void	display_map(t_cub *cub)
{
    draw_tiles(cub);
	draw_player(&cub->cfg->player, cub);
	draw_rays(cub);
}
