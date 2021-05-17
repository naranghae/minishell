/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:56:18 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/17 17:42:39 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	exec_not_built_in(t_cmd *exec_cmd, char **path, char **envp)
{
	pid_t	pid;
	int		res;
	int		status;
	int		i;
	char	*join;
	char	*pathjoin;

	i = 0;
	res = 0;
	if (exec_cmd->has_pip)
		if (pipe(exec_cmd->fd) < 0)
			exit(0);
			//exit_fatal();
	pid = fork();
	if (pid < 0)
		exit(0);
		//exit_fatal();
	else if (pid == 0)
	{
		if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
			exit(0);
			//exit_fatal();
		if (exec_cmd->prev && exec_cmd->prev->has_pip && dup2(exec_cmd->prev->fd[0], 0) < 0)
			exit(0);
			//exit_fatal();
		while (path[i] != NULL)
		{
			join = ft_strjoin(path[i], "/");
			pathjoin = ft_strjoin(join, exec_cmd->cmd[0]);
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(write(1,"error\n",6) * 0);
			res = execve(pathjoin, exec_cmd->cmd, envp);
			free(path[i]);
			free(join);
			free(pathjoin);
			i++;
		}
		exit(res);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
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

void	exec_cmd(t_cmd **cmd, char **envp, char **path, t_env **env_set)
{
	t_cmd	*exec_cmd;

	// {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	exec_cmd = (*cmd)->next;
	while (exec_cmd != (*cmd)->tail)
	{
		if (!ft_strncmp(exec_cmd->cmd[0], "cd", 2))
			exec_cd(exec_cmd);
		else if (!ft_strncmp(exec_cmd->cmd[0], "env", 2))
			exec_env(exec_cmd, env_set);
		else
			exec_not_built_in(exec_cmd, path, envp);
		exec_cmd = exec_cmd->next;
	}

}

int		exec(t_cmd **cmd, t_env **env_set, char **envp)
{
	t_env	*exec_env;
	char	**path;

	exec_env = *env_set;
	while (exec_env != NULL)
	{
		if (!ft_strncmp(exec_env->name, "PATH", 4))
			path = ft_split(exec_env->contents,':'); //leaks
		exec_env = exec_env->next;
	}
	exec_cmd(cmd, envp, path, env_set);
	return (0);
}
