// static void draw_frame(t_cub *cub);
// static int loop_hook(void *param);
// static int on_key(int keycode, void *param);
// static void put_pixel(char *addr, int bpp, int ll, int x, int y, int color);

// static int	init_map_grid(t_config *cfg)
// {
// 	int		i;
// char *rows[] = {
//     "1111111111111111111111111",
//     "1100000000110000000000001",
//     "1011000001110000000000001",
//     "1101000000000000000000001",
//     "111111111011000001110000000000001",
//     "100000000011000001110111111111111",
//     "11110111111111011100000010001",
//     "11110111111111011101010010001",
//     "11000000110101011100000010001",
//     "10000000000000001100000010001",
//     "10000000000000001101010010001",
//     "1100000111010101111101111000111",
//     "11110111 1110101 101111010001",
//     "11111111 1111111 111111111111",
//     NULL
// };


// 	cfg->map.height = 14;
// 	cfg->map.width = 34;
		

// 	cfg->map.grid = heap_manager(sizeof(char *) * cfg->map.height, 'a', 0);
// 	if (!cfg->map.grid)
// 		return (0);
// 	i = 0;
// 	while (i < cfg->map.height)
// 	{
// 		cfg->map.grid[i] = ft_strdup(rows[i]);
// 		if (!cfg->map.grid[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static void	player_view_init(t_config *config);

// static t_config	*fake_config(void)
// {
// 	t_config	*cfg;

// 	cfg = heap_manager(sizeof(t_config), 'a', 0);
// 	if (!cfg)
// 		return (NULL);
// 	cfg->north = ft_strdup("./assets/north.xpm");
// 	cfg->south = ft_strdup("./assets/south.xpm");
// 	cfg->west = ft_strdup("./assets/west.xpm");
// 	cfg->east = ft_strdup("./assets/east.xpm");
// 	cfg->floor.r = 50;
// 	cfg->floor.g = 50;
// 	cfg->floor.b = 50;
// 	cfg->floor.value = (50 << 16) | (50 << 8) | 50;
// 	cfg->ceiling.r = 150;
// 	cfg->ceiling.g = 150;
// 	cfg->ceiling.b = 150;
// 	cfg->ceiling.value = (150 << 16) | (150 << 8) | 150; 
// 	if (!init_map_grid(cfg))
// 		return (NULL);
// 	cfg->player.pos[X] = 2 + 0.5
// 	cfg->player.pos[Y] = 2 + 0.5;
// 	cfg->player.dir = 'N';
// 	player_view_init(cfg);
// 	return (cfg);
// } 
// static void	destroy_image(t_cub *g, t_tex_img *img)
// {
// 	if (img->img)
// 	{
// 		mlx_destroy_image(g->mlx, img->img);
// 		img->img = NULL;
// 		img->addr = NULL;
// 	}
// }

// static void	release_textures(t_cub *g)
// {
// 	int	i;

// 	i = 0;
// 	while (i < TEX_COUNT)
// 	{
// 		destroy_image(g, &g->textures[i]);
// 		i++;
// 	}
// }

// static void	destroy_display(t_cub *g)
// {
// 	if (g->win)
// 	{
// 		mlx_destroy_window(g->mlx, g->win);
// 		g->win = NULL;
// 	}
// 	if (g->mlx)
// 	{
// 		mlx_destroy_display(g->mlx);
// 		free(g->mlx);
// 		g->mlx = NULL;
// 	}
// }

// static int	on_x(t_cub *g)
// {
// 	release_textures(g);
// 	heap_manager(0, 'f', 0);
// 	destroy_display(g);
// 	exit(0);
// 	return (0);
// }

// static char	*resolve_texture_path(const char *path)
// {
// 	char	*prefixed;

// 	if (!path)
// 		return (NULL);
// 	if (access(path, F_OK) == 0)
// 		return (ft_strdup(path));
// 	prefixed = ft_strjoin("engine/", path);
// 	if (prefixed && access(prefixed, F_OK) == 0)
// 		return (prefixed);
// 	free(prefixed);
// 	return (NULL);
// }

// static int	load_texture(void *mlx, t_tex_img *dst, const char *path)
// {
// 	char	*resolved;

// 	resolved = resolve_texture_path(path);
// 	if (!resolved)
// 	{
// 		fprintf(stderr, "Texture path not found: %s\n", path);
// 		return (0);
// 	}
// 	dst->img = mlx_xpm_file_to_image(mlx, resolved, &dst->w, &dst->h);
// 	free(resolved);
// 	if (!dst->img)
// 	{
// 		fprintf(stderr, "Failed to load texture: %s\n", path);
// 		return (0);
// 	}
// 	dst->addr = mlx_get_data_addr(dst->img, &dst->bpp, &dst->ll, &dst->endian);
// 	return 1;
// }

// static int	load_textures(t_cub *cub, t_config *cfg)
// {
// 	if (!load_texture(cub->mlx, &cub->textures[TEX_NORTH], cfg->north))
// 		return (0);
// 	if (!load_texture(cub->mlx, &cub->textures[TEX_EAST], cfg->east))
// 		return (0);
// 	if (!load_texture(cub->mlx, &cub->textures[TEX_SOUTH], cfg->south))
// 		return (0);
// 	if (!load_texture(cub->mlx, &cub->textures[TEX_WEST], cfg->west))
// 		return (0);
// 	return (1);
// }

// void	start_window(t_config *cfg)
// {
// 	t_cub	cub;

// 	memset(&cub, 0, sizeof(t_cub));
// 	cub.mlx = mlx_init();
// 	if (!cub.mlx)
// 	{
// 		fprintf(stderr, "not inited\n");
// 		return ;
// 	}
// 	cub.win = mlx_new_window(cub.mlx, win_w, win_h, "cub3d");
// 	if (!cub.win)
// 	{
// 		fprintf(stderr, "not inited\n");
// 		destroy_display(&cub);
// 		return ;
// 	}
// 	cub.cfg = cfg;
// 	if (!load_textures(&cub, cfg))
// 	{
// 		release_textures(&cub);
// 		destroy_display(&cub);
// 		return ;
// 	}
// 	mlx_hook(cub.win, 17, 0, on_x, &cub);
// 	mlx_key_hook(cub.win, on_key, &cub);
// 	draw_frame(&cub);
// 	mlx_loop_hook(cub.mlx, loop_hook, &cub);
// 	mlx_loop(cub.mlx);
// 	release_textures(&cub);
// 	destroy_display(&cub);
// }

// static void player_view_init(t_config *config)
// {
// 	static const struct {
// 		char dir;
// 		double dx, dy;
// 		double px, py;
// 	} dir_map[] = {
// 		{'N', 0.0, -1.0,  0.66,  0.0},
// 		{'S', 0.0,  1.0, -0.66,  0.0},
// 		{'E', 1.0,  0.0,  0.0,   0.66},
// 		{'W',-1.0,  0.0,  0.0,  -0.66},
// 		{0,   0.0,  0.0,  0.0,   0.0}
// 	};
// 	int i = 0;
// 	while (dir_map[i].dir)
// 	{
// 		if (config->player.dir == dir_map[i].dir)
// 		{
// 			config->player.dir_view[0] = dir_map[i].dx;
// 			config->player.dir_view[1] = dir_map[i].dy;
// 			config->player.plane[0] = dir_map[i].px;
// 			config->player.plane[1] = dir_map[i].py;
// 			return;
// 		}
// 		++i;
// 	}
// 	config->player.dir_view[0] = 0.0;
// 	config->player.dir_view[1] = -1.0;
// 	config->player.plane[0] = 0.66;
// 	config->player.plane[1] = 0.0;
// }

// static void put_pixel(char *addr, int bpp, int ll, int x, int y, int color)
// {
// 	if (x < 0 || x >= win_w || y < 0 || y >= win_h)
// 		return;
// 	char *dst = addr + (y * ll + x * (bpp / 8));
// 	*(unsigned int *)dst = color;
// }

// static void draw_frame(t_cub *cub)
// {
// 	t_config *cfg = cub->cfg;
// 	void *mlx = cub->mlx;
// 	char **map = cfg->map.grid;
// 	double posX = cfg->player.pos[X];
// 	double posY = cfg->player.pos[Y];
// 	double dirX = cfg->player.dir_view[0];
// 	double dirY = cfg->player.dir_view[1];
// 	double planeX = cfg->player.plane[0];
// 	double planeY = cfg->player.plane[1];

// 	void *img = mlx_new_image(mlx, win_w, win_h);
// 	int bpp, ll, endian;
// 	char *addr = mlx_get_data_addr(img, &bpp, &ll, &endian);

// 	int x = 0;
// 	while (x < win_w)
// 	{
// 		double cameraX = 2 * x / (double)win_w - 1;
// 		double rayDirX = dirX + planeX * cameraX;
// 		double rayDirY = dirY + planeY * cameraX;

// 		int mapX = (int)posX;
// 		int mapY = (int)posY;

// 		double deltaDistX;
// 		if (fabs(rayDirX) < 1e-8)
// 			deltaDistX = 1e30;
// 		else
// 			deltaDistX = fabs(1 / rayDirX);
// 		double deltaDistY;
// 		if (fabs(rayDirY) < 1e-8)
// 			deltaDistY = 1e30;
// 		else
// 			deltaDistY = fabs(1 / rayDirY);

// 		double sideDistX;
// 		double sideDistY;

// 		int stepX;
// 		int stepY;
// 		int hit = 0;
// 		int side = 0;

// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (posX - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
// 		}

// 		while (!hit)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if (mapY >= 0 && mapY < cfg->map.height && mapX >= 0 && mapX < cfg->map.width && map[mapY][mapX] == '1')
// 				hit = 1;
// 			else if (!(mapY >= 0 && mapY < cfg->map.height && mapX >= 0 && mapX < cfg->map.width))
// 				break;
// 		}

// 		double perpWallDist;
// 		if (side == 0)
// 		{
// 			double denom;
// 			if (rayDirX == 0)
// 				denom = 1e-6;
// 			else
// 				denom = rayDirX;
// 			perpWallDist = (mapX - posX + (1 - stepX) / 2) / denom;
// 		}
// 		else
// 		{
// 			double denom;
// 			if (rayDirY == 0)
// 				denom = 1e-6;
// 			else
// 				denom = rayDirY;
// 			perpWallDist = (mapY - posY + (1 - stepY) / 2) / denom;
// 		} 

// 		if (perpWallDist <= 0)
// 			perpWallDist = 1e-6;

// 		int lineHeight = (int)(win_h / perpWallDist);
// 		int drawStart = -lineHeight / 2 + win_h / 2;
// 		int drawEnd = lineHeight / 2 + win_h / 2;
// 		if (drawStart < 0) drawStart = 0;
// 		if (drawEnd >= win_h) drawEnd = win_h - 1;

// 		int y = 0;
// 		while (y < drawStart)
// 		{
// 			put_pixel(addr, bpp, ll, x, y, cfg->ceiling.value);
// 			y++;
// 		}

// 		y = drawStart;
// 		t_tex_img *tex = NULL;
// 		if (side == 0)
// 		{
// 			if (rayDirX > 0)
// 				tex = &cub->textures[TEX_WEST];
// 			else
// 				tex = &cub->textures[TEX_EAST];
// 		}
// 		else
// 		{
// 			if (rayDirY > 0)
// 				tex = &cub->textures[TEX_NORTH];
// 			else
// 				tex = &cub->textures[TEX_SOUTH];
// 		}

// 			int texW = tex->w;
// 			int texH = tex->h;
// 			int tbpp = tex->bpp;
// 			int tll = tex->ll;
// 			char *taddr = (char *)tex->addr;

// 			double wallX;
// 			if (side == 0)
// 				wallX = posY + perpWallDist * rayDirY;
// 			else
// 				wallX = posX + perpWallDist * rayDirX;
// 			wallX -= floor(wallX);
// 			int texX = (int)(wallX * (double)texW);
// 			if (side == 0 && rayDirX > 0) texX = texW - texX - 1;
// 			if (side == 1 && rayDirY < 0) texX = texW - texX - 1;

// 			double stepTex = (double)texH / (double)lineHeight;
// 			double texPos = (drawStart - win_h / 2 + lineHeight / 2) * stepTex;

// 			while (y <= drawEnd)
// 			{
// 				int texY = (int)texPos;
// 				if (texY < 0) texY = 0;
// 				if (texY >= texH) texY = texH - 1;
// 				char *p = taddr + texY * tll + texX * (tbpp / 8);
// 				unsigned int color = *(unsigned int *)p;

// 				if (side == 1)
// 					color = ((color >> 1) & 0x7F7F7F);
// 				put_pixel(addr, bpp, ll, x, y, color);
// 				texPos += stepTex;
// 				y++;
// 			}

// 		y = drawEnd + 1;
// 		while (y < win_h)
// 		{
// 			put_pixel(addr, bpp, ll, x, y, cfg->floor.value);
// 			y++;
// 		}

// 		x++;
// 	}

// 	mlx_put_image_to_window(mlx, cub->win, img, 0, 0);
// 	mlx_destroy_image(mlx, img);
// }

// static int loop_hook(void *param)
// {
// 	draw_frame((t_cub *)param);
// 	return (0);
// }

// static int on_key(int keycode, void *param)
// {
// 	t_cub *cub = (t_cub *)param;
// 	t_config *cfg = cub->cfg;
// 	double moveSpeed = 0.3;
// 	double rotSpeed = 0.3;

// 	if (keycode == 65307)
// 	{
// 		on_x(cub);
// 		return (0);
// 	}

// 	if (keycode == 119 || keycode == 87)
// 	{
// 		cfg->player.pos[X] += cfg->player.dir_view[0] * moveSpeed;
// 		cfg->player.pos[Y] += cfg->player.dir_view[1] * moveSpeed;
// 	}
// 	else if (keycode == 115 || keycode == 83)
// 	{
// 		cfg->player.pos[X] -= cfg->player.dir_view[0] * moveSpeed;
// 		cfg->player.pos[Y] -= cfg->player.dir_view[1] * moveSpeed;
// 	}

// 	else if (keycode == 97 || keycode == 65)
// 	{
// 		cfg->player.pos[X] -= cfg->player.plane[0] * moveSpeed;
// 		cfg->player.pos[Y] -= cfg->player.plane[1] * moveSpeed;
// 	}
// 	else if (keycode == 100 || keycode == 68)
// 	{
// 		cfg->player.pos[X] += cfg->player.plane[0] * moveSpeed;
// 		cfg->player.pos[Y] += cfg->player.plane[1] * moveSpeed;
// 	}

// 	else if (keycode == 65361)
// 	{
// 		double oldDirX = cfg->player.dir_view[0];
// 		double oldPlaneX = cfg->player.plane[0];
// 		cfg->player.dir_view[0] = cfg->player.dir_view[0] * cos(rotSpeed) - cfg->player.dir_view[1] * sin(rotSpeed);
// 		cfg->player.dir_view[1] = oldDirX * sin(rotSpeed) + cfg->player.dir_view[1] * cos(rotSpeed);
// 		cfg->player.plane[0] = cfg->player.plane[0] * cos(rotSpeed) - cfg->player.plane[1] * sin(rotSpeed);
// 		cfg->player.plane[1] = oldPlaneX * sin(rotSpeed) + cfg->player.plane[1] * cos(rotSpeed);
// 	}
// 	else if (keycode == 65363)
// 	{
// 		double oldDirX = cfg->player.dir_view[0];
// 		double oldPlaneX = cfg->player.plane[0];
// 		double ang = -rotSpeed;
// 		cfg->player.dir_view[0] = cfg->player.dir_view[0] * cos(ang) - cfg->player.dir_view[1] * sin(ang);
// 		cfg->player.dir_view[1] = oldDirX * sin(ang) + cfg->player.dir_view[1] * cos(ang);
// 		cfg->player.plane[0] = cfg->player.plane[0] * cos(ang) - cfg->player.plane[1] * sin(ang);
// 		cfg->player.plane[1] = oldPlaneX * sin(ang) + cfg->player.plane[1] * cos(ang);
// 	}

// 	draw_frame(cub);
// 	return (0);
// }