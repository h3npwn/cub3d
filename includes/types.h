/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:41:13 by abahja            #+#    #+#             */
/*   Updated: 2025/12/31 19:16:06 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# define X					0
# define Y					1
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

# define TEX_N				0
# define TEX_S				1
# define TEX_W				2
# define TEX_E				3
typedef unsigned long	t_color;

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
	ERR_TEXTURE,
	ERR_UNKNOWN
}	t_error;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		endian;
	int		width;
	int		height;
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

typedef struct s_movements
{
	char	m_left;
	char	m_right;
	char	m_up;
	char	m_down;
	char	c_left;
	char	c_right;
}	t_movements;

typedef struct s_ray
{
	double	dir[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	perp_dist;
	int		map[2];
	int		steps[2];
	int		side;
}	t_ray;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	char		*map_path;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	char		initial_dir;
	t_ray		ray;
	t_movements	moves;
	t_color		f_color;
	t_color		c_color;
	t_img_frame	img_frame;
	t_img_frame tex[4];
	t_map		map;
	// t_texture	texture;
	t_player	player;
}	t_cub3d;

#endif
