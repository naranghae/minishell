/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:23:42 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/14 21:11:08 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		listlen(t_env *env_info)
{
	t_env	*envcount;
	int		i;

	i = 0;
	envcount = env_info->next;
	while (envcount != NULL)
	{
		if (envcount->equal)
			i++;
		envcount = envcount->next;
	}
	return (i);
}

int		listlen_all(t_env *env_info)
{
	t_env	*envcount;
	int		i;

	i = 0;
	envcount = env_info->next;
	while (envcount != NULL)
	{
		i++;
		envcount = envcount->next;
	}
	return (i);
}

void	write_env(t_env *exec_env)
{
	if (exec_env->equal)
		printf("%s=%s\n", exec_env->name, exec_env->contents);
}

int		exec_env(t_env *env_info)
{
	t_env	*exec_env;

	exec_env = env_info->next;
	while (exec_env != NULL)
	{
		write_env(exec_env);
		exec_env = exec_env->next;
	}
	return (0);
}

int		pre_exec_env(t_cmd *exec_cmd, pid_t *pid, t_env *env_info)
{
	int status;
	int res;

	res = 0;
	status = 0;
	if (exec_cmd->has_pip || exec_cmd->prev->has_pip)
	{
		if (*pid == 0)
		{
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(1);
			if (exec_cmd->prev && exec_cmd->prev->has_pip &&
				dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(1);
			exit(exec_env(env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, status);
		return (0);
	}
	else
		return (exec_env(env_info));
}
