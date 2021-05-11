/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:15:37 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/10 17:34:52 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		sub_sp(char const *s, char c, char **new_str)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c && k == i)
			k++;
		else if (s[i] == c)
		{
			new_str[j] = ft_substr(s, k, (i - k));
			j++;
			k = i + 1;
		}
		i++;
	}
	if (i != k)
		new_str[j++] = ft_substr(s, k, (i - k));
	new_str[j] = 0;
}

char			**ft_split(char const *s, char c)
{
	char		**new_str;

	if (!s)
		return (NULL);
	if (!(new_str = (char **)malloc(sizeof(char *) * (1 + ft_strlen(s)))))
		return (NULL);
	sub_sp(s, c, new_str);
	return (new_str);
}
