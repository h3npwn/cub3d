
#ifndef CUB3D_H
# define CUB3D_H

/*------------------------------------------*/
// # define COLS 14
// # define ROWS 9
# define X 0
# define Y 1
# define TILE_SIZE 32
# define FOV 60 * (M_PI / 180)
# define WINDOW_WIDTH   (TILE_SIZE)
# define WINDOW_HEIGHT  (TILE_SIZE)
# define RES 4
# define NUM_RAYS  (WINDOW_WIDTH / RES)
/*------------------------------------------*/
//#define win_w
//#define win_h 

# include "../../minilibx-linux/mlx.h"
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef enum e_error
{
	ERR_ARGC = 0,
	ERR_FILE,
	ERR_CONFIG,
	ERR_MALLOC,
	ERR_MAP,
	ERR_UNKNOWN
}	t_error;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	value; // (r << 16 | g << 8 | b)
}	t_rgb;


typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;
typedef  struct s_ray
{
	double ray_angle;
	double wall_hit_x;
	double wall_hit_y;
	double distance;
	int tail_size;
}	t_ray;

typedef struct s_player
{
	double	pos[2];
	double	dir_view[2];
	double	plane[2];
	double	move_speed;
	double	radius;
	double	rot_speed;
	double	rot_angle;
	int		walk_direction;
	int		turn_direction;
	char	dir;	// 'N' 'S' 'E' 'W'
}	t_player;

typedef struct s_config
{
	void		*mlx;
	void		*win;
	char		*filename;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			num_rays;
	t_ray		*rays;
	t_rgb		floor;
	t_rgb		ceiling;
	t_map		map;
	t_player	player;
}	t_config;

typedef struct s_tex_img
{
	void	*img;
	void	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
}	t_tex_img;



typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3
# define TEX_COUNT 4

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_tex_img	frame;
	t_tex_img	textures[TEX_COUNT];
	t_config	*cfg;
}	t_cub;

void		ft_config(t_config *config);
void		fill_rgb(t_rgb *rgb, char *line);
int			isvalid(char *line, t_config	*config);
int			file_check(const char *file, const char *ext);
void		read_path_texture(int fd, t_config *config);
void		print_config(t_config *config);
char		*get_next_line(int fd);
void		exit_failure(int code, int isnoexit);
t_config	*init(char **av);
void		bfs(t_map map, char **copy, int start_x, int start_y);
void		check_inside_map(t_map map, char **copy);
void		check_chars(char *line, t_config *config);
/*-------------------*/
void		print_config(t_config *cfg);
void	render_scene(t_config *config);
void mlx_draw_circle(void *mlx, void *win, int center_x, int center_y, int color);
void mlx_draw_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color);
void mlx_draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color);
/*-------------------*/

#endif
