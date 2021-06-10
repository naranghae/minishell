/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:26:22 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 21:26:33 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		exec_built_in(t_cmd *exec_cmd, t_env **env_info)
{
	pid_t	pid;
	int		re;

	re = 0;
	if (exec_cmd->has_pip)
		pipe_fork(exec_cmd, &pid);
	if (!ft_strncmp(exec_cmd->cmd[0], "cd", 2))
		re = pre_exec_cd(exec_cmd, &pid);
	else if (!ft_strncmp(exec_cmd->cmd[0], "echo", 4))
		re = pre_exec_echo(exec_cmd, &pid);
	else if (!ft_strncmp(exec_cmd->cmd[0], "env", 3))
		re = pre_exec_env(exec_cmd, &pid, *env_info);
	else if (!ft_strncmp(exec_cmd->cmd[0], "exit", 4))
		re = pre_exec_exit(exec_cmd, &pid);
	else if (!ft_strncmp(exec_cmd->cmd[0], "export", 6))
		re = pre_exec_export(exec_cmd, &pid, *env_info);
	else if (!ft_strncmp(exec_cmd->cmd[0], "unset", 5))
		re = pre_exec_unset(exec_cmd, &pid, *env_info);
	else if (!ft_strncmp(exec_cmd->cmd[0], "pwd", 3))
		re = pre_exec_pwd(exec_cmd, &pid);
	else if (!ft_strncmp(exec_cmd->cmd[0], "$?", 2))
		re = pre_exec_exit_code(exec_cmd, &pid);
	g_errcode = re;
	return (re);
}

int		is_built_in(t_cmd *exec_cmd)
{
	if (!ft_strncmp(exec_cmd->cmd[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "env", 3))
		return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "exit", 4))
		return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "export", 6))
		return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "$?", 2))
		return (1);
	else
		return (0);
}

void	exec_redirection(t_cmd *exec_cmd)
{
	t_red *tmp;

	tmp = exec_cmd->red;
	printf("filename %s type%d\n", tmp->file_name, tmp->type);
	while (tmp != NULL)
	{
		if (tmp->type == IN)
		{
			if (!(tmp->fd = open(tmp->file_name, O_RDONLY, 0644)))
				return ;
			if (dup2(tmp->fd, 0) < 0)
				exit(0);
		}
		else if (tmp->type == OUT)
		{
			if (!(tmp->fd = open(tmp->file_name,
				O_CREAT | O_WRONLY | O_TRUNC, 0644)))
				return ;
			if (dup2(tmp->fd, 1) < 0)
				exit(0);
		}
		else if (tmp->type == APPEND)
		{
			if (!(tmp->fd = open(tmp->file_name,
				O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644)))
				return ;
			if (dup2(tmp->fd, 1) < 0)
				exit(0);
		}
		tmp = tmp->next;
	}
}

void	close_fd(t_red *red)
{
	while (red != NULL)
	{
		close(red->fd);
		red = red->next;
	}
}

void	exec_cmd(t_cmd **cmd, t_env **env_set, char **path)
{
	t_cmd	*exec_cmd;
	int		tmp_in;
	int		tmp_out;
	t_cmd	*exec_cmd_a;

	tmp_in = dup(0);
	tmp_out = dup(1);
	exec_cmd = (*cmd)->next;
	if ((*env_set)->envp)
		free_split((*env_set)->envp);
	(*env_set)->envp = get_envp(*env_set);
	if (exec_cmd == NULL || exec_cmd->cmd[0] == NULL || ft_strlen(exec_cmd->cmd[0]) < 1)
		return ;
	while (exec_cmd != (*cmd)->tail)
	{
		exec_cmd_a = exec_cmd;
		change_qute(&exec_cmd, *env_set, 0);
		if (exec_cmd->red != NULL)
			exec_redirection(exec_cmd);
		if (is_built_in(exec_cmd))
			exec_built_in(exec_cmd, env_set);
		else
			exec_not_built_in(exec_cmd, path, (*env_set)->envp);
		if (exec_cmd->red!= NULL)
		{
			dup2(tmp_out, 1);
			dup2(tmp_in, 0);
			close_fd(exec_cmd->red);
		}
		exec_cmd = exec_cmd->next;
	}
}

int		exec(t_cmd **cmd, t_env **env_info)
{
	t_env	*exec_env;
	char	**path;
	int		i;

	i = -1;
	set_termios(SIGON);
	exec_env = *env_info;
	while (exec_env->next != NULL)
	{
		exec_env = exec_env->next;
		if (!ft_strncmp(exec_env->name, "PATH", 4))
			path = ft_split(exec_env->contents, ':');
	}
	exec_cmd(cmd, env_info, path);
	free_split(path);
	return (0);
}