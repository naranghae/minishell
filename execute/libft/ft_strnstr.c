/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:47:14 by chanykim          #+#    #+#             */
/*   Updated: 2020/10/07 20:15:02 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*find)
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		if (str[i] == find[j])
		{
			while (i + j < len && str[i + j] == find[j])
			{
				j++;
				if (!find[j])
					return ((char *)&str[i]);
			}
		}
		i++;
	}
	return (NULL);
}
