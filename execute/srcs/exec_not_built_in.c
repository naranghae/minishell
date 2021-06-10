/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:31:42 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 14:30:48 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

char	**get_envp(t_env *env_set)
{
	int		i;
	int		k;
	char	*ejoin;
	char	*envjoin;
	char	**envpp;
	t_env	*env_parse;

	k = 0;
	env_parse = env_set->next;
	i = listlen(env_set);
	envpp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envpp)
		return (NULL);
	while (env_parse != NULL)
	{
		if (env_parse->contents)
		{
			ejoin = ft_strjoin(env_parse->name, "=");
			envjoin = ft_strjoin(ejoin, env_parse->contents);
			envpp[k++] = envjoin;
			free(ejoin);
		}
		env_parse = env_parse->next;
	}
	envpp[k] = NULL;
	return (envpp);
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
	if (pipe(exec_cmd->fd) < 0)
		exit(0);
	pid = fork();
	g_gv.child = 1;
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
			exit(0);
		if (exec_cmd->prev && exec_cmd->prev->has_pip &&
			dup2(exec_cmd->prev->fd[0], 0) < 0)
			exit(0);
		while (path[i] != NULL)
		{
			pjoin = ft_strjoin(path[i], "/");
			pathjoin = ft_strjoin(pjoin, exec_cmd->cmd[0]);
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(write(1, "error\n", 6) * 0);
			if (!ft_strncmp(exec_cmd->cmd[0], "/bin/", 5))
				res = execve(exec_cmd->cmd[0], exec_cmd->cmd, envp);
			else
				res = execve(pathjoin, exec_cmd->cmd, envp);
			free(path[i]);
			free(pjoin);
			free(pathjoin);
			i++;
		}
		exit(printf("no cmd\n") * 0 + res);// add exitcode 127
	}
	else if (pid > 0)
		close_pipe(&pid, exec_cmd, res, status);
}
