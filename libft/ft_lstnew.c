/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:09:37 by abahja            #+#    #+#             */
/*   Updated: 2024/11/05 10:44:29 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*listnew;

	listnew = heap_manager(sizeof(t_list), 'a', 0);
	if (!listnew)
		return (NULL);
	listnew->content = content;
	listnew->next = NULL;
	return (listnew);
}
