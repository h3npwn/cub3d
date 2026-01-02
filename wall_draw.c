/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:02:52 by mochajou          #+#    #+#             */
/*   Updated: 2026/01/02 22:28:24 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	f_c_paint(t_cub3d *cub3d, int x)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		img_pixel_put(&cub3d->img_frame, x, y, cub3d->c_color);
		img_pixel_put(&cub3d->img_frame, x, y + WIN_HEIGHT / 2, cub3d->f_color);
		y++;
	}
	if (cub3d->ray.side == 0)
	{
		if (cub3d->ray.dir[X] > 0)
			return (TEX_W);
		return (TEX_E);
	}
	if (cub3d->ray.dir[Y] > 0)
		return (TEX_N);
	return (TEX_S);
}

int	calculate_start_end(int line_height, int *draw_start, int *draw_end)
{
	*draw_start = (WIN_HEIGHT - line_height) / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = *draw_start + line_height;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT;
	return (0);
}

static unsigned int	get_tex_color(t_img_frame *tex)
{
	char	*src;

	if (tex->tex_x < 0 || tex->tex_x >= tex->width)
		tex->tex_x = (tex->tex_x < 0) * tex->width;
	if (tex->tex_y < 0 || tex->tex_y >= tex->height)
		tex->tex_y = (tex->tex_y < 0) * tex->height;
	src = tex->addr + (tex->tex_y * tex->size_line
			+ tex->tex_x * (tex->pix_bits / 8));
	return (*(unsigned int *)src);
}

void	test_wall(t_cub3d *cub3d, int x, t_img_frame *tex)
{
	double	step;
	double	tex_pos;
	int		draw_start;
	int		draw_end;
	int		line_height;

	line_height = (int)(WIN_HEIGHT / cub3d->ray.perp_dist);
	calculate_start_end(line_height, &draw_start, &draw_end);
	step = (double)tex->height / line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	while (draw_start < draw_end)
	{
		tex->tex_y = (int)tex_pos;
		tex_pos += step;
		img_pixel_put(&cub3d->img_frame, x, draw_start, get_tex_color(tex));
		draw_start++;
	}
}

void	draw_walls(t_cub3d *cub3d, int x)
{
	t_ray			*ray;
	t_img_frame		*tex;
	double			wall_x;
	int				compass;

	ray = &cub3d->ray;
	compass = f_c_paint(cub3d, x);
	if (cub3d->ray.perp_dist <= 0.0)
		cub3d->ray.perp_dist = 0.0001;
	wall_x = cub3d->player.pos[(ray->side == 0)]
		+ cub3d->ray.perp_dist * ray->dir[(ray->side == 0)];
	wall_x -= floor(wall_x);
	tex = &cub3d->tex[compass];
	tex->tex_x = (int)(wall_x * (double)(tex->width));
	test_wall(cub3d, x, tex);
}
