/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:31:42 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/15 16:48:04 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

char	**get_envp(t_env *env_set)
{
	t_get_env var;

	var.k = 0;
	var.env_parse = env_set->next;
	var.i = listlen_all(env_set);
	var.envpp = (char **)malloc(sizeof(char *) * (var.i + 1));
	if (!var.envpp)
		return (NULL);
	while (var.env_parse != NULL)
	{
		if (var.env_parse->equal == 1)
		{
			var.ejoin = ft_strjoin(var.env_parse->name, "=");
			var.envpp[var.k++] = ft_strjoin(var.ejoin, var.env_parse->contents);
			free(var.ejoin);
		}
		else if (var.env_parse->equal == 0)
			var.envpp[var.k++] = ft_strdup(var.env_parse->name);
		var.env_parse = var.env_parse->next;
	}
	var.envpp[var.k] = NULL;
	return (var.envpp);
}

void	not_built_in_free(char *path, char *pjoin, char *pathjoin)
{
	free(path);
	free(pjoin);
	free(pathjoin);
}

void	command_error(char *cmd, char **path, int type)
{
	if (type == 1)
	{
		if (path == NULL)
		{
			ft_putstr_fd("hyochanyoung: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
	}
	else if (type == 0)
	{
		g_errcode = 127;
		ft_putstr_fd("hyochanyoung: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(g_errcode);
	}
}

void	command_not_built_in(t_cmd *exec_cmd, char **path, char **envp, int i)
{
	char	*pjoin;
	char	*pathjoin;

	while (path[i] != NULL)
	{
		pjoin = ft_strjoin(path[i], "/");
		pathjoin = ft_strjoin(pjoin, exec_cmd->cmd[0]);
		if (exec_cmd->red == NULL)
		{
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(write(2, "error\n", 6) * 0);
		}
		else
		{
			if (exec_cmd->has_pip && dup2(exec_cmd->red->fd, 1) < 0)
				exit(write(2, "error\n", 6) * 0);
		}
		if (i == 0)
			execve(exec_cmd->cmd[0], exec_cmd->cmd, envp);
		else
			execve(pathjoin, exec_cmd->cmd, envp);
		not_built_in_free(path[i], pjoin, pathjoin);
		i++;
	}
}

void	exec_not_built_in(t_cmd *exec_cmd, char **path, char **envp)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	g_errcode = 0;
	if (pipe(exec_cmd->fd) < 0)
		exit(0);
	pid = fork();
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
			exit(1);
		if (exec_cmd->prev && exec_cmd->prev->has_pip &&
			dup2(exec_cmd->prev->fd[0], 0) < 0)
			exit(1);
		command_error(exec_cmd->cmd[0], path, 1);
		command_not_built_in(exec_cmd, path, envp, 0);
		command_error(exec_cmd->cmd[0], path, 0);
	}
	else if (pid > 0)
		close_pipe(&pid, exec_cmd, status);
}
