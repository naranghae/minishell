/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/08 19:30:19 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	swap_list(t_env *env, t_env *env_next)
{
	char	*tmp_name;
	char	*tmp_contents;
	int		tmpequal;

	tmpequal = 0;
	tmp_name = env->name;
	env->name = env_next->name;
	env_next->name = tmp_name;
	tmp_contents = env->contents;
	env->contents = env_next->contents;
	env_next->contents = tmp_contents;
	tmpequal = env->equal;
	env->equal = env_next->equal;
	env_next->equal = tmpequal;
}

void	env_sort_print(t_env *env_info)
{
	t_env	*env_sort;
	int		list_num;
	int		i;
	int		j;
	int		max;

	max = 0;
	i = -1;
	j = -1;
	env_info = env_info->next;
	env_sort = env_info;
	list_num = listlen_all(env_sort);
	while (++i <= list_num)
	{
		if (env_sort->next == NULL)
			break ;
		while (++j <= list_num - 1 - i)
		{
			max = ft_strlen(env_sort->name) > ft_strlen(env_sort->next->name) ?\
			ft_strlen(env_sort->name) : ft_strlen(env_sort->next->name);
			if (ft_strncmp(env_sort->name, env_sort->next->name, max) > 0)
				swap_list(env_sort, env_sort->next);
			env_sort = env_sort->next;
		}
		j = -1;
		env_sort = env_info;
	}
	while (env_info != NULL)
	{
		if (env_info->equal)
			printf("declare -x %s=\"%s\"\n",
				env_info->name, env_info->contents);
		else
			printf("declare -x %s\n", env_info->name);
		env_info = env_info->next;
	}
}
