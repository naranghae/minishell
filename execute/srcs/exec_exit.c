/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:24:02 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/14 20:33:58 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		ft_exit(int exitcode)
{
	write(1, "exit\n", 5);
	g_errcode = exitcode;
	exit(exitcode);
}

int		is_number(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int		exec_exit(t_cmd *exec_cmd)
{
	if (exec_cmd->has_pip || exec_cmd->prev->has_pip)
		return (0);
	if (exec_cmd->cmd[1] == NULL)
		ft_exit(g_errcode);
	else if (exec_cmd->cmd[1] != NULL && !is_number(exec_cmd->cmd[1]))
	{
		printf("exit: %s: numeric argument required\n", exec_cmd->cmd[1]);
		ft_exit(255);
	}
	else if (exec_cmd->cmd[1] != NULL && is_number(exec_cmd->cmd[1]))
		ft_exit(ft_atoi(exec_cmd->cmd[1]));
	return (0);
}

int		pre_exec_exit(t_cmd *exec_cmd, pid_t *pid)
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
				exit(0);
			if (exec_cmd->prev && exec_cmd->prev->has_pip &&
				dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(0);
			exit(exec_exit(exec_cmd));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
		return (0);
	}
	else
		return (exec_exit(exec_cmd));
}
