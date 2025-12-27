/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:44:42 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 16:08:01 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	mlx_inits(t_cub3d* cfg)
{
	cfg->mlx = mlx_init();
	if (!cfg->mlx)
		exit_failure(ERR_INIT, 1);
	cfg->win = mlx_new_window(cfg->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cfg->win)
		exit_failure(ERR_INIT, 1);
	cfg->img_frame.img = mlx_new_image(cfg->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cfg->img_frame.img)
		exit_failure(ERR_INIT, 1);
	cfg->img_frame.addr = mlx_get_data_addr(cfg->img_frame.img,
			&cfg->img_frame.pix_bits, &cfg->img_frame.size_line,
			&cfg->img_frame.endian);
	if (!cfg->img_frame.addr)
		exit_failure(ERR_INIT, 1);

	printf("bits per pixel: %d\n", cfg->img_frame.pix_bits / 8);
}
void	img_pixel_put(t_img_frame *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->pix_bits / 8));

	*(unsigned int *)dst = color;
}
void	mlx_clear_image(t_img_frame *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			img_pixel_put(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}
void	mlx_destroy_all(t_cub3d *cfg)
{
	if (cfg->img_frame.img)
		mlx_destroy_image(cfg->mlx, cfg->img_frame.img);
	if (cfg->win)
		mlx_destroy_window(cfg->mlx, cfg->win);
	if (cfg->mlx)
	{
		mlx_destroy_display(cfg->mlx);
		free(cfg->mlx);
	}
}
