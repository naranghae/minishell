/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/16 15:35:04 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

char	*remove_quot(char *s)
{
	char	*re;
	int		re_i;
	int		i;

	i = 0;
	re_i = 0;
	re = s;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			i++;
			continue ;
		}
		else
			re[re_i++] = s[i];
		i++;
	}
	re[re_i] = '\0';
	return (re);
}

char	**delete_quot(char **export_cmd)
{
	int i;

	i = 0;
	while (export_cmd[i])
	{
		if (ft_strchr(export_cmd[i], '"') || ft_strchr(export_cmd[i], '\''))
			export_cmd[i] = remove_quot(export_cmd[i]);
		i++;
	}
	return (export_cmd);
}

int		parsing_check_env(t_cmd *cmd, t_env *env_info)
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
		error = except_check(export_cmd[i], 1);
		if ((cmd->cmd[1] != NULL) && cmd->has_pip)
			return (1);
		else if ((cmd->cmd[1] != NULL) && cmd->prev->has_pip)
			return (1);
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
	if (parsing_check_env(exec_cmd, env_info))
		return (1);
	return (0);
}

int		pre_exec_export(t_cmd *exec_cmd, pid_t *pid, t_env *env_info)
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
				exit(1);
			if (exec_cmd->prev && exec_cmd->prev->has_pip &&
				dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(1);
			exit(exec_export(exec_cmd, env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, status);
		return (0);
	}
	else
		return (exec_export(exec_cmd, env_info));
}
