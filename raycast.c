/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 23:41:19 by mochajou          #+#    #+#             */
/*   Updated: 2025/12/30 15:25:19 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_ray(t_cub3d *cub3d, int x)
{
	double	cam_x;

	cam_x = 2.0 * x / (double)WIN_WIDTH -1;
	cub3d->ray.dir[X] = cub3d->player.dir_x + cub3d->player.plane_x * cam_x;
	cub3d->ray.dir[Y] = cub3d->player.dir_y + cub3d->player.plane_y * cam_x;
	cub3d->ray.map[X] = cub3d->player.posx;
	cub3d->ray.map[Y] = cub3d->player.posy;
	cub3d->ray.delta_dist[X] = 1e30;
	cub3d->ray.delta_dist[Y] = 1e30;
	if (cub3d->ray.dir[X] != 0)
		cub3d->ray.delta_dist[X] = fabs(1.0 / cub3d->ray.dir[X]);
	if (cub3d->ray.dir[Y] != 0)
		cub3d->ray.delta_dist[Y] = fabs(1.0 / cub3d->ray.dir[Y]);
}

void	compelete_dda_utils(t_ray *ray, int ax, double pos)
{
	if (ray->dir[ax] < 0)
	{
		ray->steps[ax] = -1;
		ray->side_dist[ax] = (pos - ray->map[ax]) * ray->delta_dist[ax];
	}
	else
	{
		ray->steps[ax] = 1;
		ray->side_dist[ax] = (ray->map[ax] + 1.0 - pos) * ray->delta_dist[ax];
	}
}

double	dda_utils(t_cub3d *cub3d)
{
	t_ray	*ray;

	ray = &cub3d->ray;
	compelete_dda_utils(ray, X, cub3d->player.posx);
	compelete_dda_utils(ray, Y, cub3d->player.posy);
	while (1336)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->map[X] += ray->steps[X];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->map[Y] += ray->steps[Y];
			ray->side = 1;
		}
		if (cub3d->map.grid[ray->map[Y]][ray->map[X]] == '1')
			break ;
	}
	if (ray->side == 0)
		return (ray->side_dist[X] - ray->delta_dist[X]);
	return (ray->side_dist[Y] - ray->delta_dist[Y]);
}

void	cast_rays(t_cub3d *cub3d)
{
	double	perp_wall_dist;
	int		x;
	int		start[2];
	int		end[2];

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(cub3d, x);
		perp_wall_dist = dda_utils(cub3d);
		start[X] = (int)(cub3d->player.posx * TILE_SIZE);
		start[Y] = (int)(cub3d->player.posy * TILE_SIZE);
		end[X] = (int)((cub3d->player.posx
					+ cub3d->ray.dir[X] * perp_wall_dist) * TILE_SIZE);
		end[Y] = (int)((cub3d->player.posy
					+ cub3d->ray.dir[Y] * perp_wall_dist) * TILE_SIZE);
		draw_line(&cub3d->img_frame, start[X], start[Y], end[X], end[Y], RED);
		x++;
	}
}
