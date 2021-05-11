/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:46:01 by chanykim          #+#    #+#             */
/*   Updated: 2020/10/05 17:31:12 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char*)ptr;
	while (i < num)
	{
		str[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
