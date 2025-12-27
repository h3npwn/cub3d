/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:38:27 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 18:38:39 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_game(char **argv, t_cub3d *cub3d)
{
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->map_path = argv[1];
	ft_init_map(cub3d);
	set_directions(cub3d);
	mlx_inits(cub3d);
}

int	render_frame(t_cub3d *cub3d)
{
	mlx_clear_image(&cub3d->img_frame);
	apply_movements(cub3d);
	draw_map2d(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_frame.img, 0, 0);
	return (0);
}

void	game(t_cub3d *cub3d)
{
	usleep(6000);
	mlx_loop_hook(cub3d->mlx, render_frame, cub3d);
	mlx_hook(cub3d->win, 2, 1L << 0, &key_press, cub3d);
	mlx_hook(cub3d->win, 3, 1L << 1, &key_release, cub3d);
	mlx_hook(cub3d->win, 17, 0L, destroy_exit, cub3d);
	mlx_loop(cub3d->mlx);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		exit_failure(ERR_ARGC, 1);
	init_game(argv, &cub3d);
	game(&cub3d);
	return (0);
}
