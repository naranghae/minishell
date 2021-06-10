/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 21:01:57 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		parsing_check_env(char *cmd, t_env *env_info)
{
	char			*tmp;
	char			**export_cmd;
	int				i;
	int				error;

	error = 0;
	i = -1;
	tmp = cmd;
	export_cmd = ft_split(tmp, ' ');
	while (export_cmd[++i] != NULL)
	{
		error = except_check(export_cmd[i], 1);
		if (error == 0)
			env_add(export_cmd[i], env_info);
	}
	free_split(export_cmd);
	if (error > 0)
		return (1);
	return (0);
}

int		exec_export(t_cmd *exec_cmd, t_env *env_info)
{
	if (exec_cmd->cmd[1] == NULL)
	{
		envsort_print(env_info->envp);
		return (0);
	}
	if ((exec_cmd->cmd[1] != NULL) && exec_cmd->has_pip)
		return (1);
	if ((exec_cmd->cmd[1] != NULL) && exec_cmd->prev->has_pip)
		return (1);
	if (parsing_check_env(exec_cmd->cmd[1], env_info))
		return (1);
	return (0);
}

int		pre_exec_export(t_cmd *exec_cmd, pid_t *pid, t_env *env_info)
{
	int	status;
	int	res;

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
			exit(exec_export(exec_cmd, env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
		return (0);
	}
	else
		return (exec_export(exec_cmd, env_info));
}
