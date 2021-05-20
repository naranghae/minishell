#include "minishell_header.h"
#include "minishell_parsing.h"


void	exec_built_in(t_cmd *exec_cmd, t_env **envp)
{
	pid_t pid;
	if (exec_cmd->has_pip)
		pipe_fork(exec_cmd, &pid);
	// if (exec_cmd->red->type != 0)
	// 	exec_red();
	if (!ft_strncmp(exec_cmd->cmd[0], "cd", 2))
		pre_exec_cd(exec_cmd, pid);
	// else if (!ft_strncmp(exec_cmd->cmd[0], "echo", 4))
	// 	pre_exec_echo();
	else if (!ft_strncmp(exec_cmd->cmd[0], "env", 3))
		pre_exec_env(exec_cmd, &pid,envp);
	// else if (!ft_strncmp(exec_cmd->cmd[0], "exit", 4))
	// 	pre_exec_exit();
	// else if (!ft_strncmp(exec_cmd->cmd[0], "export", 6))
	// 	pre_exec_export();
	// else if (!ft_strncmp(exec_cmd->cmd[0], "unset", 5))
	// 	pre_exec_unset();
	// else if (!ft_strncmp(exec_cmd->cmd[0], "pwd", 3))
	// 	pre_exec_pwd();
	else
		return ;
}

int		is_built_in(t_cmd *exec_cmd)
{
	if (!ft_strncmp(exec_cmd->cmd[0], "cd", 2))
		return (1);
	// else if (!ft_strncmp(exec_cmd->cmd[0], "echo", 4))
	// 	return (1);
	else if (!ft_strncmp(exec_cmd->cmd[0], "env", 3))
		return (1);
	// else if (!ft_strncmp(exec_cmd->cmd[0], "exit", 4))
	// 	return (1);
	// else if (!ft_strncmp(exec_cmd->cmd[0], "export", 6))
	// 	return (1);
	// else if (!ft_strncmp(exec_cmd->cmd[0], "unset", 5))
	// 	return (1);
	// else if (!ft_strncmp(exec_cmd->cmd[0], "pwd", 3))
		// return (1);
	else
		return (0);
}


void exec_redirection(t_cmd *exec_cmd)
{
	t_red *tmp;
	
	tmp = exec_cmd->red;
	printf("filename %s type%d\n", tmp->file_name, tmp->type);
	while (tmp != NULL)
	{
		if (tmp->type == IN)
		{
			if (!(tmp->fd = open (tmp->file_name,O_RDONLY, 0644)))
			return ;
			if (dup2(tmp->fd, 0) < 0)
				exit(0);
		}
		else if (tmp->type == OUT)
		{
			if (!(tmp->fd = open (tmp->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
			return ;
			if (dup2(tmp->fd, 1) < 0)
				exit(0);
		}
		else if (tmp->type == APPEND)
		{
			if (!(tmp->fd = open (tmp->file_name, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644)))
			return ;
			if (dup2(tmp->fd, 1) < 0)
				exit(0);
		}
		tmp = tmp->next;
	}
	// dup2(tmp_out, 1);
	// close (*fd);
}

void close_fd(t_red *red)
{
	while (red != NULL)
	{
		close(red->fd);
		red = red->next;
	}
}
void	exec_cmd(t_cmd **cmd, t_env **env_set, char **envp, char **path)
{
	t_cmd	*exec_cmd;
	int tmp_in;
	int tmp_out;
	
	tmp_in = dup(0);
	tmp_out = dup(1);
	exec_cmd = (*cmd)->next;
	if (exec_cmd->cmd[0] == NULL)
		return ;
	while (exec_cmd != (*cmd)->tail)
	{
		if (exec_cmd->red != NULL && exec_cmd->red->type != 0)
			exec_redirection(exec_cmd);
		if (is_built_in(exec_cmd))
			exec_built_in(exec_cmd, env_set);
		else
			exec_not_built_in(exec_cmd, path, envp);
		if (exec_cmd->red!= NULL)
		{
			dup2(tmp_out, 1);
			dup2(tmp_in, 0);
			close_fd (exec_cmd->red);
		}
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
	exec_cmd(cmd, env_set, envp, path);
	free_split(path);
	return (0);
}
