/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:42:40 by abahja            #+#    #+#             */
/*   Updated: 2026/01/04 21:34:14 by mochajou         ###   ########.fr       */
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
