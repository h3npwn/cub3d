
#ifndef CUB3D_H
# define CUB3D_H

/*------------------------------------------*/
// # define COLS 14
// # define ROWS 9
# define X 0
# define Y 1
# define TILE_SIZE 50
# define FOV (60 * (M_PI / 180))
# define WINDOW_WIDTH   (TILE_SIZE)
# define WINDOW_HEIGHT  (TILE_SIZE)
# define RES 5
# define NUM_RAYS  (WINDOW_WIDTH / RES)
/*------------------------------------------*/
//#define win_w
//#define win_h 

# include <mlx.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
#include <stdbool.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


typedef enum e_error
{
	ERR_ARGC = 0,
	ERR_FILE,
	ERR_CONFIG,
	ERR_MALLOC,
	ERR_MAP,
	ERR_INIT,
	ERR_UNKNOWN
}	t_error;
# define BLACK				0x000000
# define WHITE				0xFFFFFF
# define RED				0xFF0000
# define GREEN				0x00FF00
# define BLUE				0x0000FF
# define DARK_BLUE			0x00008B
# define YELLOW				0xFFFF00
# define CYAN				0x00FFFF
# define MAGENTA			0xFF00FF
# define GRAY				0x808080
# define LIGHT_GRAY			0xD3D3D3
# define DARK_GRAY			0x404040
# define ORANGE				0xFFA500
# define PURPLE				0x800080
# define BROWN				0xA52A2A

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

	double rayangle;
	double wallhitx;
	double wallhity;
	bool was_hit_vertical;
	bool was_hit_horizontal;
	bool is_facing_up;
	bool is_facing_down;
	bool is_facing_left;
	bool is_facing_right;
	int wall_hit_content;
	// int wall_content;
}	t_ray;

typedef struct s_player
{
  	double	pos[2]; // x, y
	double	rot_angle;

    double		width;
    double		height;
    int			turnDirection; // -1 for left, +1 for right
    int			walkDirection; // -1 for back, +1 for front
    double		rotationAngle;
    double		walkSpeed;
    double		turnSpeed;
	char		dir; /* 'N' 'S' 'E' 'W' */
}	t_player;

typedef struct s_config
{
	char		*filename;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	t_rgb		floor;
	t_player	player;
	t_rgb		ceiling;
	t_map		map;
}	t_config;

typedef struct s_tex_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
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
	unsigned int	win_h;
	unsigned int	win_w;
	unsigned int	num_rays;
	void			*mlx;
	void			*win;
	t_tex_img		frame;
	t_ray			*rays;
	t_tex_img		textures[TEX_COUNT];
	t_config		*cfg;
}	t_cub;

void		ft_config(t_config *config);
void		fill_rgb(t_rgb *rgb, char *line);
int			isvalid(char *line, t_config	*config);
int			file_check(const char *file, const char *ext);
void		read_path_texture(int fd, t_config *config);
void		print_config(t_config *config);
char		*get_next_line(int fd);
void		exit_failure(int code, int isnoexit);
t_config	*init(char **av, t_cub *cub);
void		bfs(t_map map, char **copy, int start_x, int start_y);
void		check_inside_map(t_map map, char **copy);
void		check_chars(char *line, t_config *config);
/*-------------------*/
void		print_config(t_config *cfg);
void		render_scene(t_config *config);

void		img_pixel_put(t_tex_img *img, int x, int y, int color);
void		draw_circle(t_tex_img *img, int center_x, int center_y, int color);
void		draw_rectangle(t_tex_img *img, int x, int y, int width, int height, int color);
void		draw_line(t_tex_img *img, int x0, int y0, int x1, int y1, int color);
void		draw_player(t_player *player, t_cub *cub);
void		mlx_draw_circle(void *mlx, void *win, int center_x, int center_y, int color);
void		mlx_draw_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color);
void		mlx_draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color);
void		frame_init(t_cub *cub);
void		frame_clear(t_tex_img *img, int w, int h);
void		render_3d_view(t_cub *cub);
void		load_textures(t_cub *cub);
double	normalize_angle(double angle);
void	player_set_angle(t_config *config, double angle);
void	player_locate_spawn(t_config *config);
void	parse_map(t_config *config, int fd);
void	player_view_init(t_config *config);
void	combine_chunks(t_list *chunks, t_config *config, int count_lines);
void	copy_map(t_map map);
void	player_inits(t_cub *cub);
char	*skip_empty_lines(int fd);
void player_inits(t_cub *cub);
void	display_map(t_cub *cub);
void	draw_player(t_player *player, t_cub *cub);
/*-------------------*/

#endif
