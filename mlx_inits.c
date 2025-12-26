/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:44:42 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 00:49:28 by abahja           ###   ########.fr       */
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
}
