/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:31:52 by chanykim          #+#    #+#             */
/*   Updated: 2020/10/15 15:33:35 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char *s;
	size_t				i;
	unsigned char		stop;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	stop = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == stop)
			return (&(d[i + 1]));
		i++;
	}
	return (NULL);
}
