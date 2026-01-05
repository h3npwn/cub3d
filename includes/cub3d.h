/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:38:00 by abahja            #+#    #+#             */
/*   Updated: 2026/01/05 04:14:38 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "dependencies.h"
# include "types.h"
# include "settings.h"
# include "keymapping.h"

/*----- Parsing -----*/
void	ft_init_map(t_cub3d *config);
void	parse_map(t_cub3d *config, int fd);
void	read_path_texture(int fd, t_cub3d *config);
char	*get_next_line(int fd);
void	bfs(t_map map, char **copy, int start_x, int start_y);

/*----- Free & Exit -----*/
void	exit_failure(int code, int isnoexit);
int		destroy_exit(t_cub3d *cub3d);
void	mlx_destroy_all(t_cub3d *cfg);

/*-------------------*/
/*----- Utils -----*/
/*-------------------*/
void	set_directions(t_cub3d *cfg);
void	mlx_inits(t_cub3d *cfg);

/*-------------player movements & events handle-------------*/
void	move(t_cub3d *cub3d, double x, double y);
void	player_rotation(t_cub3d *cub3d, double angle);
void	apply_movements(t_cub3d *cub3d);
int		key_press(int key, t_cub3d *cub3d);
int		key_release(int key, t_cub3d *cub3d);

/*-----------raycasting-------------*/
void	cast_rays(t_cub3d *cub3d);
void	draw_walls(t_cub3d *cub3d, int x);

#endif
