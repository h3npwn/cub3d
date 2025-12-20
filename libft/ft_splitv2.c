/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:32:22 by mochajou          #+#    #+#             */
/*   Updated: 2025/06/15 00:52:02 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cw(const char *s, char *mask)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = 0;
	while (mask[i] && s[i])
	{
		if (mask[i] != '0')
		{
			++ret;
			while (mask[i] && mask[i] != '0')
				++i;
		}
		else
			++i;
	}
	return (ret);
}

static void	ft_mc(char **card, char const *s, char *mask)
{
	size_t	i;
	size_t	j;
	size_t	c_index;

	i = 0;
	c_index = 0;
	while (mask[i] && s[i])
	{
		while (s[i] && mask[i] == '0')
			i++;
		j = i;
		while (s[i] && mask[i] != '0')
			i++;
		card[c_index] = ft_substr(s, j, (i - j));
		c_index++;
	}
}

char	**bash_split(const char *s, char *mask)
{
	char	**ret;
	size_t	cw;

	if (!s || !mask)
		return (NULL);
	cw = ft_cw(s, mask);
	ret = heap_manager(sizeof(char *) * (cw + 1), 'x', 0);
	if (!ret)
		return (0);
	ft_mc(ret, s, mask);
	ret[cw] = 0;
	if (!ret || !ret[0])
	{
		ret = heap_manager(sizeof(char *) * 2, 'x', 0);
		ret[0] = ft_strdup("");
		ret[1] = NULL;
	}
	return (ret);
}
