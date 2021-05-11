/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:54:37 by chanykim          #+#    #+#             */
/*   Updated: 2020/10/14 18:08:34 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int		ft_atoi(const char *str)
{
	int						sign;
	unsigned long long		sol;

	sign = 1;
	sol = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		sol = sol * 10 + *str - '0';
		if (sign == 1 && sol > LLONG_MAX)
			return (-1);
		else if (sign == -1 && sol > LLONG_MAX - 1)
			return (0);
		str++;
	}
	return (sign * sol);
}
