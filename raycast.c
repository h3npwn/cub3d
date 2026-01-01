/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 23:41:19 by mochajou          #+#    #+#             */
/*   Updated: 2026/01/01 23:00:20 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <mlx.h>

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
void	f_c_paint(t_cub3d *cub3d, int x)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		img_pixel_put(&cub3d->img_frame, x, y, cub3d->c_color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		img_pixel_put(&cub3d->img_frame, x, y, cub3d->f_color);
		y++;
	}
}
int	calculate_start_end(int line_height, int *draw_start, int *draw_end)
{
	*draw_start = (WIN_HEIGHT - line_height ) / 2;
	if (*draw_start < 0)
		*draw_start = 0;

	*draw_end = *draw_start + line_height;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT;;
	return (0);
}

static int	select_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir[X] > 0)
			return (TEX_W);
		return (TEX_E);
	}
	if (ray->dir[Y] > 0)
		return (TEX_N);
	return (TEX_S);
}

static unsigned int	get_tex_color(t_img_frame *tex, int tex_x, int tex_y)
{
	char	*src;

	if (tex_x < 0 || tex_x >= tex->width)
		tex_x = (tex_x < 0) * tex->width;
	if (tex_y < 0 || tex_y >= tex->height)
		tex_y = (tex_y < 0) * tex->height;
	src = tex->addr + (tex_y * tex->size_line + tex_x * (tex->pix_bits / 8));
	return (*(unsigned int *)src);
}

void 	draw_walls(t_cub3d *cub3d, int x, double perp_wall_dist)
{
	t_ray			*ray;
	t_img_frame		*tex;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	f_c_paint(cub3d, x);
	ray = &cub3d->ray;
	if (perp_wall_dist <= 0.0)
		perp_wall_dist = 0.0001;
	line_height = (int)(WIN_HEIGHT / perp_wall_dist);
	calculate_start_end(line_height, &draw_start, &draw_end);
	if (ray->side == 0)
		wall_x = cub3d->player.posy + perp_wall_dist * ray->dir[Y];
	else
		wall_x = cub3d->player.posx + perp_wall_dist * ray->dir[X];
	wall_x -= floor(wall_x);
	tex = &cub3d->tex[select_texture(ray)];
	tex_x = (int)(wall_x * (double)(tex->width));
	step = (double)tex->height / line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	while (draw_start < draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_tex_color(tex, tex_x, tex_y);
		img_pixel_put(&cub3d->img_frame, x, draw_start, color);
		draw_start++;
	}
}

void	cast_rays(t_cub3d *cub3d)
{
	double	perp_wall_dist;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(cub3d, x);
		perp_wall_dist = dda_utils(cub3d);
		draw_walls(cub3d, x, perp_wall_dist);
		x++;
	}
}
