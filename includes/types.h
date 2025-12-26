#ifndef TYPES_H
# define TYPES_H

# define WHITE				0xFFFFFF
# define PURPLE				0x800080
# define DARK_GRAY			0x404040
# define LIGHT_GRAY			0xD3D3D3
# define BLUE				0x0000FF
# define BLACK				0x000000
# define GREEN				0x00FF00
# define YELLOW				0xFFFF00
# define DARK_BLUE			0x00008B
# define CYAN				0x00FFFF
# define RED				0xFF0000
# define MAGENTA			0xFF00FF
# define GRAY				0x808080
# define BROWN				0xA52A2A
# define ORANGE				0xFFA500

typedef unsigned long color_t;

// Linked list node for BFS
typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

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

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		endian;
	int		pix_bits;
	int		size_line;
}			t_img_frame;

typedef struct s_rgb
{
    int	r;
    int	g;
    int	b;
}	t_rgb;
typedef struct s_map
{
    char	**grid;
    int		width;
    int		height;
}	t_map;

typedef struct s_texture
{
	int		size;
	int		index;
	int		x;
	int		y;
	double	step;
	double	pos;
}					t_texture;

typedef struct s_player
{
    double	posx;
    double	posy;
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
}	t_player;
typedef struct s_rawcolor
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rawcolor;
typedef struct s_cub3d
{
    void        *mlx;
    void        *win;
    char        *map_path;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	char 	  	initial_dir;
	color_t		f_color;
	color_t		c_color;
    t_img_frame img_frame;
    t_map       map;
    t_texture   texture;
    t_player    player;
}   t_cub3d;

#endif