/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:38:00 by abahja            #+#    #+#             */
/*   Updated: 2025/12/27 22:13:22 by mochajou         ###   ########.fr       */
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
char	*skip_empty_lines(int fd);
void	copy_map(t_map map);
void	fill_rgb(t_color *color, char *line);
int		isvalid(char *line, t_cub3d	*config);
char	*get_next_line(int fd);
int		file_check(const char *file, const char *ext);
void	read_path_texture(int fd, t_cub3d *config);
void	detect_player_position(char *line, t_cub3d *config, int y);
void	combine_chunks(t_list *chunks, t_cub3d *config, int count_lines);
void	print_config(t_cub3d *config);
void	exit_failure(int code, int isnoexit);
t_cub3d	*init(char **av, t_cub3d *cub);
void	bfs(t_map map, char **copy, int start_x, int start_y);
void	check_inside_map(t_map map, char **copy);
void	check_chars(char *line, t_cub3d *config);
void	print_config(t_cub3d *cfg);
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
int		destroy_exit(t_cub3d *cub3d);
void	draw_map2d(t_cub3d *cub3d);
/*---------------------------------*/
void	img_pixel_put(t_img_frame *img, int x, int y, int color);
void	draw_circle(t_img_frame *img, int center_x, int center_y,
			int color);
void	draw_rectangle(t_img_frame *img, int x, int y,
			int width, int height, int color);
void	draw_line(t_img_frame *img, int x0, int y0,
			int x1, int y1, int color);
void	draw_player(t_player *player, t_cub3d *cub);
void	mlx_draw_circle(void *mlx, void *win, int center_x,
			int center_y, int color);
void	mlx_draw_rectangle(void *mlx, void *win, int x, int y,
			int width, int height, int color);
void	mlx_draw_line(void *mlx, void *win, int x0, int y0,
			int x1, int y1, int color);
/*----------------------------------------*/


#endif
