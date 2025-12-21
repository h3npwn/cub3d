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
#include "../gnl/get_next_line.h"
#include <ctype.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

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
void	combine_chunks(t_list *chunks, t_config *config, int count_lines)
{
	t_list *current;
	size_t	pifon;
	int 	i;

	pifon = 0;
	current = chunks;
	i = 0;
	char **rows = heap_manager(sizeof(char *) * count_lines, 'a', 0);
	if (!rows)
		exit(3);
	while (current)
	{
		rows[i] = (char *)current->content;
		if (ft_strlen(rows[i]) > pifon)
			pifon = ft_strlen(rows[i]);
		current->content = NULL;
		i++;
		current = current->next;
	}
	config->map.height = count_lines;
	config->map.width = pifon;
	config->map.grid = rows;
	rows = NULL;
}

void	parse_map(t_config *config, int fd)
{
	t_list *chunks;
	int line_count;

	line_count = 0;
	chunks = NULL;
	char *line;
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		t_list *new_chunk = ft_lstnew(line);
		ft_lstadd_back(&chunks, new_chunk);
		line_count++;
		line = get_next_line(fd);
	}
	if(line_count == 0)
		exit(3);
	combine_chunks(chunks, config, line_count);
}

void    ft_config(t_config *config)
{
	int fd = open("./maps/file", O_RDONLY);
	read_path_texture(fd, config);
	print_config(config);
	parse_map(config, fd);
	for(int i = 0; i < config->map.height; i++)
	{
		printf("%s", config->map.grid[i]);
	}
	close(fd);
	exit(0);
}