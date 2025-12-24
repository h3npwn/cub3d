#include "../headers/cub3d.h"
#include <math.h>

typedef struct s_rayhit
{
	double	distance;
	double	wall_x;
	double	dir_x;
	double	dir_y;
	int		side;
	int		tex_id;
}	t_rayhit;

static void	choose_texture(t_rayhit *hit, int step_x, int step_y)
{
	if (hit->side == 0)
		hit->tex_id = (step_x < 0) ? TEX_WEST : TEX_EAST;
	else
		hit->tex_id = (step_y < 0) ? TEX_NORTH : TEX_SOUTH;
}

static void	cast_ray(t_cub *cub, double angle, t_rayhit *hit)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit_wall;

	pos_x = cub->cfg->player.pos[X];
	pos_y = cub->cfg->player.pos[Y];
	dir_x = cos(angle);
	dir_y = sin(angle);
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	delta_dist_x = (dir_x == 0) ? 1e30 : fabs(1.0 / dir_x);
	delta_dist_y = (dir_y == 0) ? 1e30 : fabs(1.0 / dir_y);
	if (dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
	}
	if (dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
	}
	hit_wall = 0;
	while (!hit_wall)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			hit->side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			hit->side = 1;
		}
		if (map_y < 0 || map_y >= cub->cfg->map.height
			|| map_x < 0 || map_x >= (int)ft_strlen(cub->cfg->map.grid[map_y])
			|| cub->cfg->map.grid[map_y][map_x] == ' '
			|| cub->cfg->map.grid[map_y][map_x] == '1')
			hit_wall = 1;
	}
	hit->distance = (hit->side == 0) ? side_dist_x - delta_dist_x
		: side_dist_y - delta_dist_y;
	hit->dir_x = dir_x;
	hit->dir_y = dir_y;
	choose_texture(hit, step_x, step_y);
	if (hit->side == 0)
		hit->wall_x = pos_y + hit->distance * dir_y;
	else
		hit->wall_x = pos_x + hit->distance * dir_x;
	hit->wall_x -= floor(hit->wall_x);
}

static unsigned int	texture_color(t_tex_img *tex, int x, int y)
{
	char	*dst;

	if (!tex->addr)
		return (0);
	dst = tex->addr + (y * tex->line_len) + (x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	draw_column(t_cub *cub, int x, t_rayhit *hit)
{
	t_tex_img		*tex;
	int				line_h;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				y;
	unsigned int	color;

	tex = &cub->textures[hit->tex_id];
	line_h = (int)(cub->win_h / hit->distance);
	draw_start = -line_h / 2 + (cub->win_h / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_h / 2 + (cub->win_h / 2);
	if (draw_end >= (int)cub->win_h)
		draw_end = cub->win_h - 1;
	tex_x = (int)(hit->wall_x * (double)tex->width);
	if (hit->side == 0 && hit->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (hit->side == 1 && hit->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / line_h;
	tex_pos = (draw_start - cub->win_h / 2 + line_h / 2) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	y = 0;
	while (y < draw_start)
		img_pixel_put(&cub->frame, x, y++, cub->cfg->ceiling.value);
	while (y <= draw_end)
	{
		if ((int)tex_pos >= tex->height)
			tex_pos = tex->height - 1;
		color = texture_color(tex, tex_x, (int)tex_pos);
		tex_pos += step;
		// if (hit->side == 1)
		// 	color = (color >> 1) & 0x7F7F7F;
		img_pixel_put(&cub->frame, x, y++, color);
	}
	while (y < (int)cub->win_h)
		img_pixel_put(&cub->frame, x, y++, cub->cfg->floor.value);
}

void	render_3d_view(t_cub *cub)
{
	int		x;
	double	ray_angle;
	double	angle_step;
	t_rayhit	hit;

	ray_angle = cub->cfg->player.rot_angle - (FOV / 2.0);
	angle_step = FOV / (double)cub->win_w;
	x = 0;
	while (x < (int)cub->win_w)
	{
		cast_ray(cub, normalize_angle(ray_angle), &hit);
		draw_column(cub, x, &hit);
		ray_angle += angle_step;
		x++;
	}
}

static char	*trim_path(char *path)
{
	char	*trimmed;

	trimmed = ft_strtrim(path, " \n\t\r");
	if (!trimmed)
		exit_failure(ERR_MALLOC, 1);
	return (trimmed);
}

static void	load_single_texture(t_cub *cub, int idx, char *path)
{
	char	*clean;

	if (!path)
		exit_failure(ERR_CONFIG, 1);
	clean = trim_path(path);
	cub->textures[idx].img = mlx_xpm_file_to_image(
			cub->mlx,
			clean,
			&cub->textures[idx].width,
			&cub->textures[idx].height);
	if (!cub->textures[idx].img)
		exit_failure(ERR_INIT, 1);
	cub->textures[idx].addr = mlx_get_data_addr(
			cub->textures[idx].img,
			&cub->textures[idx].bpp,
			&cub->textures[idx].line_len,
			&cub->textures[idx].endian);
}

void	load_textures(t_cub *cub)
{
	load_single_texture(cub, TEX_NORTH, cub->cfg->north);
	load_single_texture(cub, TEX_SOUTH, cub->cfg->south);
	load_single_texture(cub, TEX_WEST, cub->cfg->west);
	load_single_texture(cub, TEX_EAST, cub->cfg->east);
}
