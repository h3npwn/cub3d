/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochajou <mochajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:42:09 by henix             #+#    #+#             */
/*   Updated: 2025/05/26 15:50:13 by mochajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	function(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	return (2);
}

int	counter(size_t num)
{
	int	c;

	c = 0;
	if (!num)
		c++;
	while (num)
	{
		c++;
		num /= 10;
	}
	return (c);
}

int	check_limits(size_t	n, int sign)
{
	if (sign == 1 && n > LLONG_MAX)
		return (0);
	if (sign == -1 && n - 1 > LLONG_MAX)
		return (0);
	if (counter(n * 10) > counter(LLONG_MAX))
		return (2);
	return (1);
}

long long	ft_atoi(const char *str)
{
	size_t	i;
	size_t	res;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (check_limits(res, sign) == 2)
			return (function((char *)str));
		res = res * 10 + (str[i] - '0');
		if (!check_limits(res, sign))
			return (function((char *)str));
		i++;
	}
	return (res * sign);
}
