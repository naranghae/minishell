/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:23:48 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/08 18:51:56 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		exec_cd(t_cmd *exec_cmd)
{
	char buf[1024];

	if (exec_cmd->has_pip)
		if (pipe(exec_cmd->fd) < 0)
			exit(0);
	getcwd(buf, 1024);
	if (chdir(exec_cmd->cmd[1]) == -1)
		printf("failed, cd\n");
	return (0);
}

int		pre_exec_cd(t_cmd *exec_cmd, pid_t *pid)
{
	int status;
	int res;

	res = 0;
	status = 0;
	if (exec_cmd->has_pip)
	{
		if (*pid == 0)
		{
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(1);
			if (exec_cmd->prev && exec_cmd->prev->has_pip &&
				dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(1);
			exit(exec_cd(exec_cmd));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
		return (0);
	}
	else
		return (exec_cd(exec_cmd));
}
