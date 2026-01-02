/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 00:26:34 by mochajou          #+#    #+#             */
/*   Updated: 2026/01/02 22:22:45 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_rgb(t_color *color, char *line)
{
	t_rawcolor	buffer;

	buffer.r = (unsigned char)ft_atoi(line);
	line += 2;
	while (*line && (*line < '0' || *line > '9'))
		line++;
	buffer.g = (unsigned char)ft_atoi(line);
	line += 2;
	while (*line && (*line < '0' || *line > '9'))
		line++;
	buffer.b = (unsigned char)ft_atoi(line);
	*color = (*(unsigned int *)&buffer);
	*color = (buffer.r << 16) | (buffer.g << 8) | (buffer.b);
	return ;
}

int	isvalid(char *line, t_cub3d	*config)
{
	const char	*paths[7] = {"NO ", "SO ", "EA ", "WE ", "F ", "C ", NULL};
	int			i;

	i = 0;
	while (paths[i])
	{
		if (!ft_strncmp(line, paths[i], ft_strlen(paths[i])))
		{
			if (*line == 'C')
				fill_rgb(&config->c_color, line + 2);
			else if (*line == 'F')
				fill_rgb(&config->f_color, line + 2);
			else if (*line == 'S')
				config->south_path = ft_substr(line, 3, ft_strlen(line) - 4);
			else if (*line == 'N')
				config->north_path = ft_substr(line, 3, ft_strlen(line) - 4);
			else if (*line == 'E')
				config->east_path = ft_substr(line, 3, ft_strlen(line) - 4);
			else if (*line == 'W')
				config->west_path = ft_substr(line, 3, ft_strlen(line) - 4);
			return (i + 1);
		}
		i++;
	}
	return (0);
}

int	file_check(const char *file, const char *ext)
{
	int	i;
	int	j;

	if ((!file || !ext))
		return (0);
	j = 0;
	i = ft_strlen(file) - ft_strlen(ext);
	if (i <= 0)
		return (0);
	if (file[i - 1] == '/')
		return (0);
	while (file[i] == ext[j] && ext[j])
	{
		i++;
		j++;
	}
	if (file[i] == '\0')
		return (1);
	return (0);
}

void	check_inside_map(t_map map, char **copy)
{
	int	i;
	int	j;

	i = 0;
	while (copy[i])
	{
		j = 0;
		while (copy[i][j])
		{
			if (copy[i][j] == ' ')
				bfs(map, copy, j, i);
			j++;
		}
		i++;
	}
}

void	ft_init_map(t_cub3d *config)
{
	int	fd;

	fd = open(config->map_path, O_RDONLY);
	if (!file_check(config->map_path, ".cub") || fd < 0)
		exit_failure(ERR_FILE, 1);
	read_path_texture(fd, config);
	parse_map(config, fd);
	copy_map(config->map);
	close(fd);
}
