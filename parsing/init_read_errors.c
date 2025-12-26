/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:42:40 by abahja            #+#    #+#             */
/*   Updated: 2025/12/25 23:43:14 by abahja           ###   ########.fr       */
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
		"Error\nUnknown error occurred.\n"
	};

	ft_putstr_fd(errors[code], 2);
	heap_manager(0, 'f', 0);
	exit(isnoexit);
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
			playerpos++;
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}
