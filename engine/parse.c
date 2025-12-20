/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:48:07 by mochajou          #+#    #+#             */
/*   Updated: 2025/12/20 19:09:38 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/cub3d.h"
#include "../libft/libft.h"
// #include "get_next_line.h"
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	fill_rgb(t_rgb *rgb, char *line)
{
	if (!ft_isdigit(line[0]))
		exit(2);
	rgb->r = ft_atoi(line);
	while (*line && isdigit(*line))
		line++;
	line++;
	if (!ft_isdigit(line[0]))
		exit(2);
	rgb->g = ft_atoi(line);
	while (*line && isdigit(*line))
		line++;
	line++;
	if (!ft_isdigit(line[0]))
		exit(2);
	rgb->b = ft_atoi(line);
	while (*line && isdigit(*line))
		line++;
	if (*line && *line != '\n')
		exit(2);
}
int isvalid(char *line, t_config* config)
{
	const char* paths[7] = {"NO ","SO ", "EA ", "WE ", "F ", "C ", NULL};
	int i = 0;
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
			return i + 1;
		}
		i++;
	}
	printf("\n invalid\n");
	return 0;
}
void	read_path_texture(int fd, t_config *config)
{
	char	*line;
	int			visited[6] = {0};
	int 	totalvisits = 0;
	while(totalvisits < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (*line == '\n')
			continue;
		int v = isvalid(line, config);
		if (v && !visited[v - 1])
		{
			visited[v - 1] = 1;
			totalvisits++;
		}
		else
			exit(5);
	}
}
void    ft_config(t_config *config)
{
	int fd = open("file", O_RDONLY);
	read_path_texture(fd, config);
	print_config(config);
	close(fd);
	exit(0);
}