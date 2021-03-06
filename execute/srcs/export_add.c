/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/14 21:27:07 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		equal_is(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == '=')
			return (1);
	}
	return (0);
}

void	store_contents(char **contents, t_env *env_parse, t_env *exec_env)
{
	if ((exec_env->contents != NULL) && (exec_env->equal == 1))
	{
		free(exec_env->contents);
		if (env_parse->contents)
			*contents = ft_strdup(env_parse->contents);
		else
			*contents = NULL;
	}
	else if ((exec_env->contents == NULL) && (exec_env->equal == 1))
	{
		if (env_parse->contents)
			*contents = ft_strdup(env_parse->contents);
		else
			*contents = NULL;
	}
	else if (exec_env->equal == 0)
	{
		if (env_parse->contents)
			*contents = ft_strdup(env_parse->contents);
		else
			*contents = NULL;
		if (env_parse->equal == 1)
			exec_env->equal = 1;
	}
}

int		name_search(t_env *env_parse, t_env *env_info)
{
	t_env	*exec_env;
	char	*contents;
	int		max;

	max = 0;
	contents = NULL;
	exec_env = env_info;
	while (exec_env != NULL)
	{
		max = ft_strlen(env_parse->name) > ft_strlen(exec_env->name) ?\
		ft_strlen(env_parse->name) : ft_strlen(exec_env->name);
		if (!ft_strncmp(env_parse->name, exec_env->name, max))
		{
			if (env_parse->equal == 0)
				return (1);
			store_contents(&contents, env_parse, exec_env);
			exec_env->contents = contents;
			return (1);
		}
		exec_env = exec_env->next;
	}
	return (0);
}

int		env_add(char *cmd, t_env *env_info)
{
	t_env	*env_parse;

	if (!(env_parse = (t_env *)malloc(sizeof(*env_parse))))
		return (0);
	save_env(env_parse, cmd, '=');
	if (name_search(env_parse, env_info->next))
	{
		free(env_parse->name);
		if (equal_is(cmd) && env_parse->contents != NULL)
			free(env_parse->contents);
		free(env_parse);
		return (0);
	}
	else
		add_back_env(&env_info, env_parse);
	return (0);
}
