/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:42:06 by hyopark           #+#    #+#             */
/*   Updated: 2021/06/11 13:52:20 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	env_remove(char *key, t_env **env)
{
	t_env	*env_remove;
	t_env	*env_tmp;
	int		max;

	max = 0;
	env_remove = NULL;
	env_tmp = NULL;
	while ((*env)->next != NULL)
	{
		env_remove = (*env)->next;
		max = ft_strlen(key) > ft_strlen(env_remove->name) ?\
			ft_strlen(key) : ft_strlen(env_remove->name);
		if (!ft_strncmp(key, env_remove->name, max))
		{
			env_tmp = env_remove->next;
			(*env)->next = env_tmp;
			free(env_remove->name);
			if (env_remove->contents)
				free(env_remove->contents);
			free(env_remove);
			return ;
		}
		(*env) = (*env)->next;
	}
}

void	init_errorcode(t_env **errorcode)
{
	(*errorcode) = new_env();
	(*errorcode)->contents = ft_itoa(g_errcode);
	(*errorcode)->name = ft_strdup("?");
}

void	change_qute(t_cmd **list, t_env *env, int i)
{
	int			ix;
	t_cmd		*tmp;
	t_env		*errorcode;
	t_st_end	st_end;

	errorcode = NULL;
	init_errorcode(&errorcode);
	tmp = *list;
	add_back_env(&env, errorcode);
	while (tmp != tmp->tail)
	{
		ix = 0;
		while (tmp->cmd[ix] != NULL)
		{
			if (ix == 0 && !ft_strncmp(tmp->cmd[ix], "$?", 2))
				break ;
			i = 0;
			change_env(tmp, env, ix, i);
			change_double_qute(tmp, ix, i, &st_end);
			change_escape(&tmp, ix, i);
			ix++;
		}
		tmp = tmp->next;
	}
	env_remove(errorcode->name, &env);
}
