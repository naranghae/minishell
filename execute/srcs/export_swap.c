/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/09 16:03:45 by chanykim         ###   ########.fr       */
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
/*
void	envsort_print(t_env *env_info)
{
	t_env	*envSort;
	int		listNum;
	int		i;
	int		j;
	int		max;

	max = 0;
	i = -1;
	j = -1;
				envp = getEnvp(*env_set);
	env_info = env_info->next;
	envSort = env_info;
	listNum = listlenAll(envSort);
	while (++i <= listNum)
	{
		if (envSort->next == NULL)
			break ;
		while (++j <= listNum -1 - i)
		{
			max = ft_strlen(envSort->name) > ft_strlen(envSort->next->name) ?\
			ft_strlen(envSort->name) : ft_strlen(envSort->next->name);
			if (ft_strncmp(envSort->name, envSort->next->name, max) > 0)
				swapList(envSort, envSort->next);
			envSort = envSort->next;
		}
		j = -1;
		envSort = env_info;
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
*/
void	envsort_print(char	**envp)
{
	t_env	*envSort;
	t_env	*tmp;
	int		listNum;
	int		i;
	int		j;
	int		max;
	//char	**envp;

	max = 0;
	i = -1;
	j = -1;
	envSort = parsing_env(envp);
	envSort = envSort->next;
	tmp = envSort;
	listNum = listlenAll(tmp);
	while (++i <= listNum)
	{
		if (tmp->next == NULL)
			break ;
		while (++j <= listNum -1 - i)
		{
			max = ft_strlen(tmp->name) > ft_strlen(tmp->next->name) ?\
			ft_strlen(tmp->name) : ft_strlen(tmp->next->name);
			if (ft_strncmp(tmp->name, tmp->next->name, max) > 0)
				swapList(tmp, tmp->next);
			tmp = tmp->next;
		}
		j = -1;
		tmp = envSort;
	}
	while (envSort != NULL)
	{
		if (envSort->equal)
			printf("declare -x %s=\"%s\"\n", envSort->name, envSort->contents);
		else
			printf("declare -x %s\n", envSort->name);
		envSort = envSort->next;
	}
}