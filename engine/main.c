#include "../headers/cub3d.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#define ENABLE_3D_VIEW 1

static int	is_wall(t_cub *cub, double x, double y)
{
	int	grid_x;
	int	grid_y;
	t_map	*map;

	map = &cub->cfg->map;
	grid_x = (int)x;
	grid_y = (int)y;
	return (grid_y < 0 || grid_y >= map->height || grid_x < 0
		|| grid_x >= (int)ft_strlen(map->grid[grid_y])
		|| map->grid[grid_y][grid_x] == '1');
}

static void	try_move(t_cub *cub, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = cub->cfg->player.pos[X] + dx;
	ny = cub->cfg->player.pos[Y] + dy;
	if (is_wall(cub, nx, ny))
		return ;
	cub->cfg->player.pos[X] = nx;
	cub->cfg->player.pos[Y] = ny;
}

static void	move_direction(t_cub *cub, double angle, double step)
{
	try_move(cub, cos(angle) * step, sin(angle) * step);
}

/*
** =========================
** MLX INIT
** =========================
*/

void	mlx_init_ptrs(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_failure(ERR_INIT, 1);

	cub->win = mlx_new_window(
		cub->mlx,
		cub->win_w,
		cub->win_h,
		"cub3d"
	);
	if (!cub->win)
		exit_failure(ERR_INIT, 1);
}

/*
** =========================
** FRAME BUFFER
** =========================
*/

void	frame_init(t_cub *cub)
{
	cub->frame.img = mlx_new_image(cub->mlx, cub->win_w, cub->win_h);
	if (!cub->frame.img)
		exit_failure(ERR_INIT, 1);
	cub->frame.width = cub->win_w;
	cub->frame.height = cub->win_h;

	cub->frame.addr = mlx_get_data_addr(
		cub->frame.img,
		&cub->frame.bpp,
		&cub->frame.line_len,
		&cub->frame.endian
	);
}

void	frame_clear(t_tex_img *img, int w, int h)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			img_pixel_put(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

/*
** =========================
** DRAW PLAYER (BUFFERED)
** =========================
*/

void	draw_player(t_player *player, t_cub *cub)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = player->pos[X] * TILE_SIZE;
	start_y = player->pos[Y] * TILE_SIZE;

	end_x = start_x + cos(player->rot_angle) * (TILE_SIZE * 3);
	end_y = start_y + sin(player->rot_angle) * (TILE_SIZE * 3);

	draw_circle(&cub->frame, start_x, start_y, GREEN);
	// draw_line(&cub->frame, start_x, start_y, end_x, end_y, RED);
}

/*
** =========================
** GAME LOOP
** =========================
*/

int	update_game(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;

	render_3d_view(cub);

	mlx_put_image_to_window(
		cub->mlx,
		cub->win,
		cub->frame.img,
		0,
		0
	);
	return (0);
}

static int	key_press(int keycode, void *param)
{
	t_cub	*cub;
	double	step;
	double	rot;

	cub = (t_cub *)param;
	step = 0.1;
	rot = 5 * (M_PI / 180);
	if (keycode == 65307)
		exit(0);
	if (keycode == 'w')
		move_direction(cub, cub->cfg->player.rot_angle, step);
	if (keycode == 's')
		move_direction(cub, cub->cfg->player.rot_angle + M_PI, step);
	if (keycode == 'a')
		move_direction(cub, cub->cfg->player.rot_angle - (M_PI / 2), step);
	if (keycode == 'd')
		move_direction(cub, cub->cfg->player.rot_angle + (M_PI / 2), step);
	if (keycode == 65361)
		player_set_angle(cub->cfg, cub->cfg->player.rot_angle - rot);
	if (keycode == 65363)
		player_set_angle(cub->cfg, cub->cfg->player.rot_angle + rot);
	return (0);
}

/*
** =========================
** INIT
** =========================
*/

t_config	*init(char **av, t_cub *cub)
{
	t_config	*config;

	config = heap_manager(sizeof(t_config), 'a', 0);
	if (!config)
		exit_failure(ERR_MALLOC, 1);

	ft_memset(config, 0, sizeof(t_config));
	config->filename = av[1];
	ft_config(config);

	cub->cfg = config;
	cub->win_w = config->map.width * TILE_SIZE;
	cub->win_h = config->map.height * TILE_SIZE;
	cub->num_rays = cub->win_w;

	player_inits(cub);
	player_view_init(cub->cfg);
	return (config);
}

/*
** =========================
** MAIN
** =========================
*/
void	img_pixel_put(t_tex_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || y < 0)
		return ;
	if (x >= img->width || y >= img->height)
		return ;

	dst = img->addr
		+ (y * img->line_len)
		+ (x * (img->bpp / 8));

	*(unsigned int *)dst = color;
}


int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		exit_failure(0, 1);

	ft_memset(&cub, 0, sizeof(t_cub));

	init(av, &cub);
	mlx_init_ptrs(&cub);
	frame_init(&cub);
	load_textures(&cub);

	mlx_hook(cub.win, 2, 1L << 0, key_press, &cub);
	mlx_loop_hook(cub.mlx, update_game, &cub);
	mlx_loop(cub.mlx);

	heap_manager(0, 'f', 0);
	return (0);
}
