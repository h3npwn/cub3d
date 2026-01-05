/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 23:41:19 by mochajou          #+#    #+#             */
/*   Updated: 2026/01/05 01:55:03 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_ray(t_cub3d *cub3d, int x)
{
	double	cam_x;

	cam_x = 2.0 * x / (double)WIN_WIDTH - 1;
	cub3d->ray.dir[X] = cub3d->player.dir[X] + cub3d->player.plane[X] * cam_x;
	cub3d->ray.dir[Y] = cub3d->player.dir[Y] + cub3d->player.plane[Y] * cam_x;
	cub3d->ray.map[X] = cub3d->player.pos[X];
	cub3d->ray.map[Y] = cub3d->player.pos[Y];
	cub3d->ray.delta_dist[X] = DBL_MAX;
	cub3d->ray.delta_dist[Y] = DBL_MAX;
	if (cub3d->ray.dir[X] != 0)
		cub3d->ray.delta_dist[X] = fabs(1.0 / cub3d->ray.dir[X]);
	if (cub3d->ray.dir[Y] != 0)
		cub3d->ray.delta_dist[Y] = fabs(1.0 / cub3d->ray.dir[Y]);
}

void	step_dir(t_ray *ray, int ax, double pos)
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
	step_dir(ray, X, cub3d->player.pos[X]);
	step_dir(ray, Y, cub3d->player.pos[Y]);
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
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(cub3d, x);
		cub3d->ray.perp_dist = dda_utils(cub3d);
		draw_walls(cub3d, x);
		x++;
	}
}
