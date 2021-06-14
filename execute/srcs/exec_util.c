/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:14:29 by hyopark           #+#    #+#             */
/*   Updated: 2021/06/14 21:09:17 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	pipe_fork(t_cmd *exec_cmd, pid_t *pid)
{
	g_errcode = 0;
	if (pipe(exec_cmd->fd) < 0)
		exit(0);
	(*pid) = fork();
	if ((*pid) < 0)
		exit(0);
}

void	close_pipe(pid_t *pid, t_cmd *exec_cmd, int status)
{
	waitpid(*pid, &status, 0);
	if (WIFEXITED(status))
		g_errcode = WEXITSTATUS(status);
	if (exec_cmd->has_pip)
	{
		close(exec_cmd->fd[1]);
		if (!exec_cmd->next)
			close(exec_cmd->fd[0]);
	}
	if (exec_cmd->prev && exec_cmd->prev->has_pip)
		close(exec_cmd->prev->fd[0]);
}

void	close_fd(t_red *red)
{
	while (red != NULL)
	{
		close(red->fd);
		red = red->next;
	}
}
