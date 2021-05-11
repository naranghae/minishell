/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:42:08 by chanykim          #+#    #+#             */
/*   Updated: 2020/10/09 20:38:01 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *s1;
	const unsigned char *s2;
	size_t				i;

	if (num <= 0)
		return (0);
	s1 = (const unsigned char *)ptr1;
	s2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < num)
	{
		if (s1[i] != s2[i])
			return ((int)(s1[i] - s2[i]));
		i++;
	}
	return (0);
}
