/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:47:59 by abahja            #+#    #+#             */
/*   Updated: 2026/01/05 04:11:52 by mochajou         ###   ########.fr       */
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

void	combine_chunks(t_list *chunks, t_cub3d *config)
{
	t_list	*current;
	size_t	pifon;
	char	**rows;
	int		i;

	pifon = 0;
	current = chunks;
	i = 0;
	rows = heap_manager(sizeof(char *) * (config->map.height + 1), 'a', 0);
	while (current)
	{
		rows[i] = (char *)current->content;
		if (ft_strlen(rows[i]) > pifon)
			pifon = ft_strlen(rows[i]);
		current->content = NULL;
		current = current->next;
		i++;
	}
	config->map.width = pifon;
	config->map.grid = rows;
	config->map.grid[config->map.height] = NULL;
	rows = NULL;
}

void	check_chars(char *line, t_cub3d *config)
{
	static int		player = 0;
	char			*playerpos;
	int				i;

	playerpos = NULL;
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(ALLOWED_ELEMENTS, line[i]) || player > 1)
			exit_failure(ERR_MAP, 1);
		playerpos = ft_strchr(VIEW_P_DIR, line[i]);
		if (playerpos)
		{
			config->initial_dir = line[i];
			config->player.pos[X] = i + 0.5;
			config->player.pos[Y] = (double)(config->map.height) + 0.5;
			line[i] = '0';
			player++;
		}
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}

void	parse_map(t_cub3d *config, int fd)
{
	t_list	*chunks;
	char	*line;

	chunks = NULL;
	line = skip_empty_lines(fd);
	while (line)
	{
		if (*line == '\n')
			break ;
		check_chars(line, config);
		ft_lstadd_back(&chunks, ft_lstnew(line));
		config->map.height++;
		line = get_next_line(fd);
	}
	if (!config->initial_dir)
		exit_failure(4, 1);
	while (line)
	{
		line = get_next_line(fd);
		if (line && *line != '\n')
			exit_failure(ERR_CONFIG, 1);
	}
	if (config->map.height == 0)
		exit_failure(3, 1);
	combine_chunks(chunks, config);
}
