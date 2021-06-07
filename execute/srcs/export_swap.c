/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/26 18:58:04 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	swapList(t_env *env, t_env *envNext)
{
	char	*tmpName;
	char	*tmpContents;
	int		tmpequal;

	tmpequal = 0;
	tmpName = env->name;
	env->name = envNext->name;
	envNext->name = tmpName;
	tmpContents = env->contents;
	env->contents = envNext->contents;
	envNext->contents = tmpContents;
	tmpequal = env->equal;
	env->equal = envNext->equal;
	envNext->equal = tmpequal;
}

void	envSort_print(t_env *env_info)
{
	t_env	*envSort;
	int		listNum;
	int		i;
	int		j;
	int		max;

	max = 0;
	i = -1;
	j = -1;
	env_info = env_info->next;
	envSort = env_info;
	listNum = listlenAll(envSort);
	while (++i <= listNum)
	{
		if (envSort->next == NULL)
			break ;
		while (++j <= listNum -1 - i)
		{
			max = ft_MAX(ft_strlen(envSort->name), ft_strlen(envSort->next->name));
			if (ft_strncmp(envSort->name, envSort->next->name, max) > 0)
				swapList(envSort, envSort->next);
			envSort = envSort->next;
		}
		j = -1;
		envSort = env_info->next;
	}
	while (env_info != NULL)
	{
		if (env_info->equal)
			printf("declare -x %s=\"%s\"\n", env_info->name, env_info->contents);
		else
			printf("declare -x %s\n", env_info->name);
		env_info = env_info->next;
	}
}
