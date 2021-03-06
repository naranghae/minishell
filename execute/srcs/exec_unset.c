/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:43:25 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/16 15:24:19 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	env_delete(char *cmd, t_env *env_info)
{
	t_env	*env_remove;
	t_env	*env_tmp;
	int		max;

	max = 0;
	env_remove = NULL;
	env_tmp = NULL;
	while (env_info->next != NULL)
	{
		env_remove = env_info->next;
		max = ft_strlen(cmd) > ft_strlen(env_remove->name) ?\
			ft_strlen(cmd) : ft_strlen(env_remove->name);
		if (!ft_strncmp(cmd, env_remove->name, max))
		{
			env_tmp = env_remove->next;
			env_info->next = env_tmp;
			free(env_remove->name);
			if (env_remove->contents)
				free(env_remove->contents);
			free(env_remove);
			return ;
		}
		env_info = env_info->next;
	}
}

int		env_unset(t_cmd *cmd, t_env *env_info)
{
	char			*tmp;
	char			**export_cmd;
	int				i;
	int				error;

	error = 0;
	i = -1;
	tmp = cmd->buf;
	export_cmd = ft_export_split(tmp, ' ');
	export_cmd = delete_quot(export_cmd);
	while (export_cmd[++i] != NULL)
	{
		if (except_unset(export_cmd[i]))
			error = 1;
		if ((cmd->cmd[1] != NULL) && cmd->has_pip)
			return (1);
		else if ((cmd->cmd[1] != NULL) && cmd->prev->has_pip)
			return (1);
		if (error == 0)
			env_delete(export_cmd[i], env_info);
	}
	free_split(export_cmd);
	return (error);
}

int		exec_unset(t_cmd *exec_cmd, t_env *env_info)
{
	if (exec_cmd->cmd[1] == NULL)
		return (0);
	else
		return (env_unset(exec_cmd, env_info));
	return (0);
}

int		pre_exec_unset(t_cmd *exec_cmd, pid_t *pid, t_env *env_info)
{
	int	status;
	int	res;

	res = 0;
	status = 0;
	if (exec_cmd->has_pip || exec_cmd->prev->has_pip)
	{
		if (*pid == 0)
		{
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(0);
			if (exec_cmd->prev && exec_cmd->prev->has_pip &&
				dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(0);
			exit(exec_unset(exec_cmd, env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, status);
		return (0);
	}
	else
		return (exec_unset(exec_cmd, env_info));
}
