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
// #include <algorithm>
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
		exit_failure(2, 1);
	rgb->r = ft_atoi(line);
	while (*line && isdigit(*line))
		line++;
	if (*line != ',' || !ft_isdigit(line[1]))
		exit_failure(2, 1);
	line++;
	rgb->g = ft_atoi(line);
	while (*line && isdigit(*line))
		line++;
	if (*line != ',' || !ft_isdigit(line[1]))
		exit_failure(2, 1);
	line++;
	rgb->b = ft_atoi(line);
	while (*line && isdigit(*line))
		line++;
	if (*line && *line != '\n')
		exit_failure(2, 1);
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
			exit_failure(ERR_MAP, 1);
	}
}
void	check_chars(char *line, t_config *config)
{
	const char		valid_chars[] = " 01NSEW\n";
	char			*playerpos;
	int				i = 0;
	static int		player = 0;

	playerpos = NULL;
	while (line[i])
	{
		if (!ft_strchr(valid_chars, line[i]) || player > 1)
			exit_failure(ERR_MAP, 1);
		playerpos = ft_strchr("NSEW", line[i]);
		if (playerpos && ++player)
			config->player.pos[X] = i;
		if (line[i] == '\n')
			line[i] = 0;
	i++;
}
	if (player == 0)
		config->player.pos[Y]++;
}
void	combine_chunks(t_list *chunks, t_config *config, int count_lines)
{
	t_list *current;
	size_t	pifon;
	int 	i;

	pifon = 0;
	current = chunks;
	i = 0;
	char **rows = heap_manager(sizeof(char *) * (count_lines + 1), 'a', 0);
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
	config->map.grid[config->map.height] = NULL;
	rows = NULL;
}

void	parse_map(t_config *config, int fd)
{
	t_list *chunks;
	int line_count;

	line_count = 0;
	chunks = NULL;
	char *line;
	while (1)
	{
		line = get_next_line(fd);
		if (*line == '\n')
			heap_manager(0,	'r', line);
		else
			break;
	}

	while (line)
	{
		if (line && *line == '\n')
			break;
		check_chars(line, config);
		t_list *new_chunk = ft_lstnew(line);
		ft_lstadd_back(&chunks, new_chunk);
		line_count++;
		line = get_next_line(fd);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (line && *line != '\n')
			exit_failure(ERR_CONFIG, 1);
	}
	if(line_count == 0)
		exit_failure(3, 1);
	combine_chunks(chunks, config, line_count);
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
void	copy_map(t_map map)
{
	char **new_grid;
	int i = 0;

	new_grid = heap_manager(sizeof(char *) * (map.height + 3), 'a', 0);
	new_grid[map.height + 2] = NULL;
	new_grid[i] = heap_manager(sizeof(char) * (map.width + 2), 'a', 0);
	ft_memset(new_grid[i], ' ', map.width + 2);
	new_grid[i][map.width + 1] = 0;
	while (map.grid[i])
	{
		new_grid[i + 1] = heap_manager(sizeof(char) * (map.width + 2), 'a', 0);
		ft_memset(new_grid[i + 1], ' ', map.width + 2);
		new_grid[i + 1][map.width + 1] = 0;
		ft_memcpy(new_grid[i + 1] + 1, map.grid[i], ft_strlen(map.grid[i]));
		i++;
	}

	new_grid[i + 1] = heap_manager(sizeof(char) * (map.width + 2), 'a', 0);
	ft_memset(new_grid[i + 1], ' ', map.width + 2);
	new_grid[i + 1][map.width + 1] = 0;
	for (int j = 0; new_grid[j]; j++)
		printf("%s\n", new_grid[j]);
	if (bfs(map, new_grid) == 0)
		exit_failure(ERR_MAP, 1);
	// map.grid = new_grid;
}

void    ft_config(t_config *config)
{
	int fd = open(config->filename, O_RDONLY);
	if (!file_check(config->filename, ".cub") || fd < 0)
		exit_failure(ERR_FILE, 1);
	read_path_texture(fd, config);
	parse_map(config, fd);
	copy_map(config->map);
	print_config(config);
	close(fd);
}