/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 00:26:34 by mochajou          #+#    #+#             */
/*   Updated: 2025/12/22 16:49:10 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../libft/libft.h"

void	fill_rgb(t_rgb *rgb, char *line)
{
	if (!ft_isdigit(line[0]))
		exit_failure(2, 1);
	rgb->r = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != ',' || !ft_isdigit(line[1]))
		exit_failure(2, 1);
	line++;
	rgb->g = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != ',' || !ft_isdigit(line[1]))
		exit_failure(2, 1);
	line++;
	rgb->b = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		line++;
	if (*line && *line != '\n')
		exit_failure(2, 1);
}

int	isvalid(char *line, t_config	*config)
{
	const char	*paths[7] = {"NO ", "SO ", "EA ", "WE ", "F ", "C ", NULL};
	int			i;

	i = 0;
	while (paths[i])
	{
		if (!ft_strncmp(line, paths[i], ft_strlen(paths[i])))
		{
			if (*line == 'C')
				fill_rgb(&config->ceiling, line + 2);
			else if (*line == 'F')
				fill_rgb(&config->floor, line + 2);
			else if (*line == 'S')
				config->south = ft_strdup(line + 3);
			else if (*line == 'N')
				config->north = ft_strdup(line + 3);
			else if (*line == 'E')
				config->east = ft_strdup(line + 3);
			else if (*line == 'W')
				config->west = ft_strdup(line + 3);
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
