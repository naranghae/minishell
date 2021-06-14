/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/14 13:21:42 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	env_clean(t_env *env_info)
{
	t_env	*envremove;
	t_env	*envtmp;

	envremove = env_info->next;
	while (envremove != NULL)
	{
		envtmp = envremove->next;
		free(envremove->name);
		if (envremove->contents)
			free(envremove->contents);
		free(envremove);
		envremove = envtmp;
	}
	free(env_info);
}

void	swaplist(t_env *env, t_env *env_next)
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

void	swap_func(t_env **tmp, t_env *envsort, int listnum)
{
	int		i;
	int		j;
	int		max;

	max = 0;
	i = -1;
	j = -1;
	while (++i <= listnum)
	{
		if ((*tmp)->next == NULL)
			break ;
		while (++j <= (listnum - 1 - i))
		{
			max = ft_strlen((*tmp)->name) > ft_strlen((*tmp)->next->name) ?\
			ft_strlen((*tmp)->name) : ft_strlen((*tmp)->next->name);
			if (ft_strncmp((*tmp)->name, (*tmp)->next->name, max) > 0)
				swaplist((*tmp), (*tmp)->next);
			(*tmp) = (*tmp)->next;
		}
		j = -1;
		(*tmp) = envsort->next;
	}
}

void	envsort_print(char **envp)
{
	t_env	*envsort;
	t_env	*tmp;
	int		listnum;

	envsort = parsing_env(envp);
	tmp = envsort->next;
	listnum = listlen_all(tmp);
	swap_func(&tmp, envsort, listnum);
	while (tmp != NULL)
	{
		if (tmp->equal == 1 && ft_strncmp("_", tmp->name,
			ft_strlen(tmp->name)) != 0)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->contents);
		else if (tmp->equal == 0)
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	env_clean(envsort);
}
