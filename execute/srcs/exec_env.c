/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:05:34 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/18 11:21:57 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	write_env(t_env	*exec_env)
{
		write(1, exec_env->name, ft_strlen(exec_env->name));
		write(1, "=", 1);
		write(1, exec_env->contents, ft_strlen(exec_env->contents));
		write(1, "\n", 1);
}

void	exec_env(t_cmd *exec_cmd, t_env **env)
{
	t_env	*exec_env;
	int		res;
	int		status;

	res = 0;
	if (exec_cmd->has_pip)
		if (pipe(exec_cmd->fd) < 0)
			exit(0);
	exec_env = *env;
	if (!exec_cmd->has_pip)
	{
		while (exec_env != NULL)
		{
			write_env(exec_env);
			exec_env = exec_env->next;
		}
	}
	else
	{
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		if (exec_cmd->has_pip)
		{
			close(exec_cmd->fd[1]);
			if (!exec_cmd->next)
				close(exec_cmd->fd[0]);
		}
		if (exec_cmd->prev && exec_cmd->prev->has_pip)
			close(exec_cmd->prev->fd[0]);
	}
}
