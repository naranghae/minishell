/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:43:25 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/07 15:32:27 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	envDelete(char *cmd, t_env *env_info)
{
	t_env	*envRemove;
	t_env	*envTmp;
	int		max;

	max = 0;
	envRemove = NULL;
	envTmp = NULL;
	while (env_info->next != NULL)
	{
		envRemove = env_info->next;
		max = ft_strlen(cmd) > ft_strlen(envRemove->name) ?\
			ft_strlen(cmd) : ft_strlen(envRemove->name);
		if (!ft_strncmp(cmd, envRemove->name, max))
		{
			envTmp = envRemove->next;
			env_info->next = envTmp;
			free(envRemove->name);
			if (envRemove->contents)
				free(envRemove->contents);
			free(envRemove);
			return ;
		}
		env_info = env_info->next;
	}
}

int		envUnset(char *cmd, t_env *env_info)
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
		if (exceptCheck(exportCmd[i], 0))
			error = 1;
		else
			envDelete(exportCmd[i], env_info);
	}
	free_split(exportCmd);
	return (error);
}

int		exec_unset(t_cmd *exec_cmd, t_env *env_info)
{
	if (exec_cmd->cmd[1] == NULL)
		return (0);
	else if ((exec_cmd->cmd[1] != NULL) && exec_cmd->has_pip)
		return (1);
	else
		return (envUnset(exec_cmd->cmd[1], env_info));
	return (0);
}

void	pre_exec_unset(t_cmd *exec_cmd, pid_t *pid, t_env *env_info)
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
			exit(exec_unset(exec_cmd, env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
	}
	else
		exec_unset(exec_cmd, env_info);
}