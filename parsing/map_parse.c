/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:47:59 by abahja            #+#    #+#             */
/*   Updated: 2025/12/25 23:41:40 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*skip_empty_lines(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (*line == '\n')
			heap_manager(0, 'r', line);
		else
			break ;
	}
	return (line);
}

void	copy_map(t_map map)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = heap_manager(sizeof(char *) * (map.height + 3), 'a', 0);
	new_grid[map.height + 2] = NULL;
	new_grid[i] = heap_manager(sizeof(char) * (map.width + 3), 'a', 0);
	ft_memset(new_grid[i], ' ', map.width + 2);
	new_grid[i][map.width + 2] = 0;
	while (map.grid[i])
	{
		new_grid[i + 1] = heap_manager(sizeof(char) * (map.width + 3), 'a', 0);
		ft_memset(new_grid[i + 1], ' ', map.width + 2);
		new_grid[i + 1][map.width + 2] = 0;
		ft_memcpy(new_grid[i + 1] + 1, map.grid[i], ft_strlen(map.grid[i]));
		i++;
	}
	new_grid[i + 1] = heap_manager(sizeof(char) * (map.width + 3), 'a', 0);
	ft_memset(new_grid[i + 1], ' ', map.width + 2);
	new_grid[i + 1][map.width + 2] = 0;
	bfs(map, new_grid, 0, 0);
	check_inside_map(map, new_grid);
}
void	detect_player_position(char *line, t_cub3d *config, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E' || line[x] == 'W')
		{
			if (config->initial_dir != 0)
				exit_failure(ERR_CONFIG, 1);
			config->initial_dir = line[x];
			config->player.posx = x + 0.5;
			config->player.posy = y + 0.5;
			line[x] = '0';
			break;
		}
		x++;
	}
}
void	combine_chunks(t_list *chunks, t_cub3d *config, int count_lines)
{
	t_list	*current;
	size_t	pifon;
	char	**rows;
	int		i;

	pifon = 0;
	current = chunks;
	i = 0;
	rows = heap_manager(sizeof(char *) * (count_lines + 1), 'a', 0);
	while (current)
	{
		rows[i] = (char *)current->content;
		if (ft_strlen(rows[i]) > pifon)
			pifon = ft_strlen(rows[i]);
		detect_player_position(rows[i], config, i);
		current->content = NULL;
		current = current->next;
		i++;
	}
	config->map.height = count_lines;
	config->map.width = pifon;
	config->map.grid = rows;
	config->map.grid[config->map.height] = NULL;
	rows = NULL;
}

void	parse_map(t_cub3d *config, int fd)
{
	t_list	*chunks;
	int		line_count;
	char	*line;
	int		row;

	line_count = 0;
	chunks = NULL;
	line = skip_empty_lines(fd);
	row = 0;
	while (line)
	{
		if (line && *line == '\n')
			break ;
		check_chars(line, config);
		ft_lstadd_back(&chunks, ft_lstnew(line));
		line_count++;
		row++;
		line = get_next_line(fd);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (line && *line != '\n')
			exit_failure(ERR_CONFIG, 1);
	}
	if (line_count == 0)
		exit_failure(3, 1);
	combine_chunks(chunks, config, line_count);
}

