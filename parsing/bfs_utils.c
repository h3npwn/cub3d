/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student-1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:31:17 by abahja            #+#    #+#             */
/*   Updated: 2025/12/23 18:46:17 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

t_node	*creat_node(int x, int y)
{
	t_node	*new;

	new = heap_manager(sizeof(t_node), 'a', 0);
	new->x = x;
	new->y = y;
	new->next = NULL;
	return (new);
}

void	enqueue(t_node **q, int x, int y)
{
	t_node	*tail;

	if (!*q)
	{
		*q = creat_node(x, y);
		return ;
	}
	tail = *q;
	while (tail->next)
		tail = tail->next;
	tail->next = creat_node(x, y);
}

t_node	*dequeue(t_node **queue)
{
	t_node	*front;

	if (!*queue)
		return (NULL);
	front = *queue;
	*queue = (*queue)->next;
	front->next = NULL;
	return (front);
}

void	move_on(t_map map, char **copy, t_node **queue, t_node *current)
{
	int			i;
	int			nx;
	int			ny;
	const char	*s = "0NSWE";
	const int	dirs[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

	i = 0;
	while (i < 4)
	{
		nx = current->x + dirs[i][0];
		ny = current->y + dirs[i][1];
		if (nx >= 0 && nx < map.width + 2 && ny >= 0 && ny < map.height + 2)
		{
			if (copy[ny][nx] && ft_strchr(s, copy[ny][nx]))
				exit_failure(ERR_MAP, 1);
			if (copy[ny][nx] != '1' && copy[ny][nx] != 'v')
			{
				copy[ny][nx] = 'v';
				enqueue(queue, nx, ny);
			}
		}
		i++;
	}
}

void	bfs(t_map map, char **copy, int start_x, int start_y)
{
	t_node	*queue;
	t_node	*current;

	queue = creat_node(start_x, start_y);
	copy[start_y][start_x] = 'v';
	while (queue)
	{
		current = dequeue(&queue);
		move_on(map, copy, &queue, current);
		heap_manager(0, 'r', current);
	}
	heap_manager(0, 'r', queue);
}
