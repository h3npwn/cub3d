/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:12:00 by mochajou          #+#    #+#             */
/*   Updated: 2025/12/20 18:31:56 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 5
// # endif

char	*new_line(char *s);
// char	*ft_substr(const char *s, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*t3mar(int fd, char **l3mara);
char	*get_next_line(int fd);

#endif
