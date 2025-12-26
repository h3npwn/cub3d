/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:19 by abahja            #+#    #+#             */
/*   Updated: 2025/06/03 14:57:07 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include "../includes/cub3d.h"

static void	ft_free(t_heapdata **heapdata)
{
	void	*ptr;

	while (*heapdata != NULL)
	{
		ptr = (*heapdata)->next;
		free((*heapdata)->ptr_h);
		free(*heapdata);
		*heapdata = (t_heapdata *)ptr;
	}
	*heapdata = NULL;
}

static t_heapdata	*new_allocation(void *ptr)
{
	t_heapdata	*node;

	node = malloc(sizeof(t_heapdata));
	if (!node)
	{
		exit_failure(ERR_MALLOC, 1);
	}
	node->ptr_h = ptr;
	node->next = NULL;
	return (node);
}

void	ft_remove(t_heapdata **heap, void *p, t_heapdata *tmp)
{
	t_heapdata	*node;

	node = *heap;
	if (node && node->ptr_h == p)
	{
		*heap = (*heap)->next;
		free(p);
		node->ptr_h = NULL;
		free(node);
		node = NULL;
		return ;
	}
	while (node)
	{
		if (node->ptr_h == p)
		{
			tmp->next = node->next;
			free(p);
			node->ptr_h = NULL;
			free(node);
			return ;
		}
		tmp = node;
		node = node->next;
	}
}

void	*collector(t_heapdata **h_d, size_t s)
{
	void	*ptr;

	ptr = malloc(s);
	if (!ptr)
		exit_failure(ERR_MALLOC, 1);
	ft_lstadd_backmalloc(h_d, new_allocation(ptr));
	return (ptr);
}

void	*heap_manager(int size, char flag, void *to_free)
{
	static t_heapdata	*heap_data = NULL;
	void				*ptr;


	ptr = NULL;
	if (flag == 'r')
		ft_remove(&heap_data, to_free, ptr);
	else if (flag == 'f')
		ft_free(&heap_data);
	else
		return collector(&heap_data, size);
	return (NULL);
}