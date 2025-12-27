/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:55:49 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 18:41:07 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_MLX_H
# define CUB_MLX_H

# include "types.h"

void	mlx_destroy_all(t_cub3d *cfg);
void	mlx_clear_image(t_img_frame *img);
void	mlx_inits(t_cub3d *cfg);
void	img_pixel_put(t_img_frame *img, int x, int y, int color);

#endif