/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/26 12:28:16 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		parsingEnv(char *cmd, t_env *env_info)
{
	char			*tmp;
	char			**exportCmd;
	int				i;
	int				error;

	error = 0;
	i = -1;
	tmp = cmd;
	exportCmd = ft_split(tmp, ' ');
	while (exportCmd[++i] != NULL)
	{
		if ((error = exceptCheck(exportCmd[i])) > 0)
		{
			if (error == 2)
				return (1);
		}
		else
			envAdd(exportCmd[i], env_info);
	}
	free_split(exportCmd);
	if (error == 1)
		return (1);
	return (0);
}

int		exec_export(t_cmd *exec_cmd, t_env *env_info)
{
	if (exec_cmd->cmd[1] == NULL)
	{
		envSort_print(env_info);
		return (0);
	}
	if ((exec_cmd->cmd[1] != NULL) && exec_cmd->has_pip)
		return (1);
	if (parsingEnv(exec_cmd->cmd[1], env_info))
		return (0);
	return (0);
}

void	pre_exec_export(t_cmd *exec_cmd, pid_t *pid, t_env *env_info)
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
				exit(0);
			if (exec_cmd->prev && exec_cmd->prev->has_pip && dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(0);
			exit(exec_export(exec_cmd, env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
	}
	else
		exec_export(exec_cmd, env_info);
}
