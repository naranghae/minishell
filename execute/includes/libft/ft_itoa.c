/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:27:19 by chanykim          #+#    #+#             */
/*   Updated: 2020/10/14 18:13:12 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	neg_check(int *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

int		num_cnt(int n)
{
	int cnt;

	cnt = 1;
	while (n /= 10)
		cnt++;
	return (cnt);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		neg;
	int		num;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg_check(&n, &neg);
	num = num_cnt(n);
	len = num + neg;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
