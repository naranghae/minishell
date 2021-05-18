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

void	exec_cmd(t_cmd **cmd, t_env **env_set, char **envp, char **path)
{
	t_cmd	*exec_cmd;

	exec_cmd = (*cmd)->next;
	while (exec_cmd != (*cmd)->tail)
	{
		if (is_built_in(exec_cmd))
			exec_built_in(exec_cmd, env_set);
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
	exec_cmd(cmd, env_set, envp, path);
	free_split(path);
	return (0);
}
