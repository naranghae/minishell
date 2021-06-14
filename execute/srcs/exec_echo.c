/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 19:21:24 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/14 19:41:43 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		exec_echo(t_cmd *exec_cmd)
{
	if (exec_cmd->has_pip)
		if (pipe(exec_cmd->fd) < 0)
			exit(0);
	if (exec_cmd->cmd[1] == NULL)
		printf("\n");
	else if (exec_cmd->cmd[1] && !ft_strncmp(exec_cmd->cmd[1], "-n", 2))
	{
		if (!ft_strncmp(exec_cmd->cmd[1], "-n ", 3))
			write(1, exec_cmd->cmd[1] + 3, ft_strlen(exec_cmd->cmd[1] + 3));
		else
			printf("");
	}
	else
		printf("%s\n", exec_cmd->cmd[1]);
	return (0);
}

int		pre_exec_echo(t_cmd *exec_cmd, pid_t *pid)
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
			exit(exec_echo(exec_cmd));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
		return (0);
	}
	else
		return (exec_echo(exec_cmd));
}
