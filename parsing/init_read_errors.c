/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:42:40 by abahja            #+#    #+#             */
/*   Updated: 2026/01/05 04:27:14 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_failure(int code, int isnoexit)
{
	const char	errors[][50] = {
		"Error\nInvalid number of arguments.\n",
		"Error\nCannot open file OR extension invalid.\n",
		"Error\nInvalid configuration format.\n",
		"Error\nMemory allocation failed.\n",
		"Error\nInvalid map format.\n",
		"Error\nInitialization failed.\n",
		"Error\nTexture file invalid.\n",
		"Error\nUnknown error occurred.\n"
	};

	ft_putstr_fd(errors[code], 2);
	heap_manager(0, 'f', 0);
	exit(isnoexit);
}

void	fill_rgb(t_color *color, char *line)
{
	t_rawcolor	buffer;

	if (!ft_isdigit(line[0]))
		exit_failure(2, 1);
	buffer.r = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != ',' || !ft_isdigit(line[1]))
		exit_failure(2, 1);
	line++;
	buffer.g = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != ',' || !ft_isdigit(line[1]))
		exit_failure(2, 1);
	line++;
	buffer.b = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line && *line != '\n')
		exit_failure(2, 1);
	*color = (buffer.r << 16) | (buffer.g << 8) | (buffer.b);
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

void	read_path_texture(int fd, t_cub3d *config)
{
	char	*line;
	int		v;
	int		visited[6];
	int		totalvisits;

	totalvisits = 0;
	ft_memset(visited, 0, sizeof(visited));
	line = NULL;
	while (totalvisits < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
			continue ;
		v = isvalid(line, config);
		if (v && !visited[v - 1])
		{
			visited[v - 1] = 1;
			totalvisits++;
		}
		else
			exit_failure(ERR_MAP, 1);
	}
}
