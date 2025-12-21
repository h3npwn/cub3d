/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:07:50 by mochajou          #+#    #+#             */
/*   Updated: 2025/12/20 18:17:37 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*new_line(char *s)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			if (s[i] == '\n')
				return ((char *)(s + i));
			i++;
		}
	}
	return (NULL);
}

static char	*no_newline(char **l3mara)
{
	char	*line;

	line = ft_strdup(*l3mara);
	heap_manager(0,'r',*l3mara);
	*l3mara = NULL;
	return (line);
}

char	*t3mar(int fd, char **l3mara)
{
	int		n;
	char	*buff;
	char	*tmp;

	buff = (char *)heap_manager(sizeof(char) * 21, 'a', NULL);
	n = 1;
	while (!new_line(*l3mara) && n > 0)
	{
		n = read(fd, buff, 20);
		if (n > 0)
		{
			buff[n] = '\0';
			tmp = *l3mara;
			if (!*l3mara)
				*l3mara = ft_strdup(buff);
			else
				*l3mara = ft_strjoin(*l3mara, buff);
			heap_manager(0,'r',tmp);
		}
	}
	heap_manager(0,'r',buff);
	return (*l3mara);
}

char	*get_next_line(int fd)
{
	static char	*l3mara;
	char		*line;
	char		*new_l;

	if (20 <= 0 || fd < 0)
		return (NULL);
	l3mara = t3mar(fd, &l3mara);
	new_l = new_line(l3mara);
	if (new_l)
	{
		line = ft_substr(l3mara, 0,(new_l - l3mara + 1));
		new_l = ft_strdup(new_l + 1);
		heap_manager(0,'r',l3mara);
		if (*new_l == '\0')
		{
			heap_manager(0,'r',new_l);
			l3mara = NULL;
		}
		else
			l3mara = new_l;
	}
	else
		line = no_newline(&l3mara);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd = open("file", O_RDWR);
// 	// exit(1);
// 	char *line = get_next_line(fd);
// 	printf("%d %s \n", fd, line);
// 	int i = 1;
// 	while (line)
// 	{
// 		printf("%s", line);
// 		heap_manager(0,'r',line);
// 		line = get_next_line(fd);
// 		getchar();
// 	}
// 	// heap_manager(0,'r',line);
// 	close(fd);
// 	// heap_manager(0, 'f', 0);
// }
