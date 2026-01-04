/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:38:27 by abahja            #+#    #+#             */
/*   Updated: 2026/01/04 23:27:36 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <mlx.h>

void	load_textures(t_cub3d *cub3d)
{
	const char	*paths[4] = {cub3d->north_path, cub3d->south_path,
		cub3d->west_path, cub3d->east_path};
	int			i;

	i = 0;
	while (i < 4)
	{
		cub3d->tex[i].img = mlx_xpm_file_to_image(cub3d->mlx, (char *)paths[i],
				&cub3d->tex[i].width, &cub3d->tex[i].height);
		if (!cub3d->tex[i].img)
		{
			mlx_destroy_all(cub3d);
			exit_failure(ERR_TEXTURE, 1);
		}
		cub3d->tex[i].addr = mlx_get_data_addr(cub3d->tex[i].img,
				&cub3d->tex[i].pix_bits, &cub3d->tex[i].size_line,
				&cub3d->tex[i].endian);
		if (!cub3d->tex[i].addr)
		{
			mlx_destroy_all(cub3d);
			exit_failure(ERR_TEXTURE, 1);
		}
		i++;
	}
}

void	init_game(char **argv, t_cub3d *cub3d)
{
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->map_path = argv[1];
	ft_init_map(cub3d);
	mlx_inits(cub3d);
	load_textures(cub3d);
	set_directions(cub3d);
}

int	render_frame(t_cub3d *cub3d)
{
	mlx_clear_image(&cub3d->img_frame);
	apply_movements(cub3d);
	cast_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img_frame.img, 0, 0);
	return (0);
}

void	game(t_cub3d *cub3d)
{
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
	print_config(&cub3d);
	game(&cub3d);
	return (0);
}
