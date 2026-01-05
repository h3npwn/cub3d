/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 00:26:34 by mochajou          #+#    #+#             */
/*   Updated: 2026/01/05 04:12:41 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
