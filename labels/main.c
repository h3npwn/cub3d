
#include "../headers/cub3d.h"
#include <mlx.h>
#include <sys/types.h>
int	is_wall(char **grid, double x, double y)
{
	int	grid_x;
	int	grid_y;
	int	row_len;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_y < 0 || grid_x < 0 || grid[grid_y] == NULL)
		return (1);
	row_len = ft_strlen(grid[grid_y]);
	if (grid_x >= row_len || grid[grid_y][grid_x] == '\0')
		return (1);
	return (grid[grid_y][grid_x] == '1' || grid[grid_y][grid_x] == ' ');
}
double distance(int x0, int y0, int x1, int y1)
{
	return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}


static int	render_loop(void *param)
{
	
	render_scene((t_config *)param);
	return (0);
}
int update(int keycode, void *param)
{
	t_cub *cub = (t_cub *)param;
	t_config *cfg = cub->cfg;
	double moveSpeed = 0.3; /* units per keypress */
	double rotSpeed = 0.3;  /* radians per keypress */

	// int
	/* Forward/back (W/S) */
	if (keycode == 119 || keycode == 87) /* 'w' or 'W' */
	{
		double nx = cfg->player->pos[X] + cfg->player->dir_view[0] * moveSpeed;
		double ny = cfg->player->pos[Y] + cfg->player->dir_view[1] * moveSpeed;
		if (!is_wall(cfg->map.grid, nx, cfg->player->pos[Y]))
			cfg->player->pos[X] = nx;
		if (!is_wall(cfg->map.grid, cfg->player->pos[X], ny))
			cfg->player->pos[Y] = ny;
	}
	else if (keycode == 115 || keycode == 83) /* 's' or 'S' */
	{
		double nx = cfg->player->pos[X] - cfg->player->dir_view[0] * moveSpeed;
		double ny = cfg->player->pos[Y] - cfg->player->dir_view[1] * moveSpeed;
		if (!is_wall(cfg->map.grid, nx, cfg->player->pos[Y]))
			cfg->player->pos[X] = nx;
		if (!is_wall(cfg->map.grid, cfg->player->pos[X], ny))
			cfg->player->pos[Y] = ny;
	}
	else if (keycode == 97 || keycode == 65)
	{
		double nx = cfg->player->pos[X] - cfg->player->plane[0] * moveSpeed;
		double ny = cfg->player->pos[Y] - cfg->player->plane[1] * moveSpeed;
		if (!is_wall(cfg->map.grid, nx, cfg->player->pos[Y]))
			cfg->player->pos[X] = nx;
		if (!is_wall(cfg->map.grid, cfg->player->pos[X], ny))
			cfg->player->pos[Y] = ny;
	}
	else if (keycode == 100 || keycode == 68)
	{
		double nx = cfg->player->pos[X] + cfg->player->plane[0] * moveSpeed;
		double ny = cfg->player->pos[Y] + cfg->player->plane[1] * moveSpeed;
		if (!is_wall(cfg->map.grid, nx, cfg->player->pos[Y]))
			cfg->player->pos[X] = nx;
		if (!is_wall(cfg->map.grid, cfg->player->pos[X], ny))
			cfg->player->pos[Y] = ny;
	}

	else if (keycode == 65361) /* left */
		player_set_angle(cfg, cfg->player->rot_angle - rotSpeed);
	else if (keycode == 65363) /* right */
		player_set_angle(cfg, cfg->player->rot_angle + rotSpeed);
	render_scene(cfg);
	return (0);
}
void mlx_initx(t_config *config)
{
	void *mlx  = NULL;
	void *win = NULL;

	mlx = mlx_init();
	if (!mlx)
	{
		fprintf(stderr, "Error\nFailed to initialize MiniLibX.\n");
		exit(EXIT_FAILURE);
	}
	win = mlx_new_window(mlx, TILE_SIZE * config->map.width, TILE_SIZE * config->map.height, "Cub3D");
	if (!mlx || !win)
	{
		fprintf(stderr, "Error\nFailed to initialize MiniLibX.\n");
		exit(EXIT_FAILURE);
	}
	printf("Player position: (%f, %f)\n", config->player->pos[X], config->player->pos[Y]);
	config->player->pos[X] += 0.5;
	config->player->pos[Y] += 0.5;
	config->mlx = mlx;
	config->win = win;
	// render_scene(config);
	// mlx_hook(win, 2, 1L << 0, update, config);
	t_cub cub;
	ft_memset(&cub, 0, sizeof(t_cub));
	cub.mlx = mlx;
	cub.win = win;
	cub.cfg = config;
	config->num_rays = (config->map.width * TILE_SIZE) / RES;
	printf("NUM_RAYS set to %d\n", config->num_rays);
	config->rays = heap_manager(sizeof(t_ray) * config->num_rays, 'a', 0);
	if (!config->rays)
		exit_failure(ERR_MALLOC, 1);
	ft_memset(config->rays, 0, sizeof(t_ray) * config->num_rays);
	// exit(1);
		// mlx_loop_hook(mlx, render_loop, config);
		render_scene(cub.cfg);
		mlx_hook(win, 2, 1L << 0, update, &cub);
		mlx_loop(mlx);
	
	// mlx_loop(mlx);
	printf("Exiting mlx_loop\n");
	// Normally you would store mlx and win in a struct for later use
}
int	main(int ac, char **av)
{
	t_config	*config;


	if (ac != 2)
		exit_failure(0, 1);
	config = init(av);
	ft_config(config);

	player_view_init(config);
	// print grid 
	for(int i = 0; i < config->map.height; i++)
		printf("%s\n", config->map.grid[i]);
	printf("\n");

	mlx_initx(config);
	heap_manager(0, 'f', 0);
}
