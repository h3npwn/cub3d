
#ifndef CUB3D_H
#define CUB3D_H
#define win_w 1220
#define win_h 600
#define X 0
#define Y 1
//#define win_w
//#define win_h 
typedef struct s_rgb
{
    int r;
    int g;
    int b;
    int value; // (r << 16 | g << 8 | b)
} t_rgb;


typedef struct s_map
{
    char    **grid;  
    int     width;
    int     height;
} t_map;

typedef struct s_player
{
    double pos[2];
    double dir_view[2];
    double plane[2];

    char    dir;    // 'N' 'S' 'E' 'W'
} t_player;

typedef struct s_config
{
    char*       filename;
    char*       north;
    char*       south;
    char*       west;
    char*       east;
    t_rgb       floor;
    t_rgb       ceiling;
    t_map       map;
    t_player    player;
} t_config;

typedef struct s_tex_img
{
	void	*img;
	void	*addr;
    int bpp;
    int ll;
    int endian;
	int		w;
	int		h;
}	t_tex_img;

#define TEX_NORTH 0
#define TEX_SOUTH 1
#define TEX_WEST 2
#define TEX_EAST 3
#define TEX_COUNT 4

typedef struct s_cub
{
    void		*mlx;
    void		*win;
    t_tex_img    frame;
	t_tex_img	textures[TEX_COUNT];
	t_config	*cfg;
} t_cub;
void    ft_config(t_config *config);
void    print_config(t_config *config);
char    *get_next_line(int fd);
#endif
