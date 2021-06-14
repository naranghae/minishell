/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:31:42 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/14 20:56:53 by chanykim         ###   ########.fr       */
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

void	exec_not_built_in(t_cmd *exec_cmd, char **path, char **envp)
{
	pid_t	pid;
	int		res;
	int		status;
	int		i;
	char	*pjoin;
	char	*pathjoin;

	res = 0;
	i = 0;
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
			exit(0);
		if (exec_cmd->prev && exec_cmd->prev->has_pip &&
			dup2(exec_cmd->prev->fd[0], 0) < 0)
			exit(0);
		if (path == NULL)
		{
			ft_putstr_fd("hyochanyoung: ", 2);
			ft_putstr_fd(exec_cmd->cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
		while (path[i] != NULL)
		{
			pjoin = ft_strjoin(path[i], "/");
			pathjoin = ft_strjoin(pjoin, exec_cmd->cmd[0]);
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(write(2, "error\n", 6) * 0);
			if (i == 0)
				res = execve(exec_cmd->cmd[0], exec_cmd->cmd, envp);
			else
				res = execve(pathjoin, exec_cmd->cmd, envp);
			not_built_in_free(path[i], pjoin, pathjoin);
			i++;
		}
		g_errcode = 127;
		ft_putstr_fd("hyochanyoung: ", 2);
		ft_putstr_fd(exec_cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(g_errcode);
	}
	else if (pid > 0)
		close_pipe(&pid, exec_cmd, res, status);
}
