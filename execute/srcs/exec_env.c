#include "minishell_header.h"
#include "minishell_parsing.h"


void	write_env(t_env	*exec_env)
{
		write(1, exec_env->name, ft_strlen(exec_env->name));
		write(1, "=", 1);
		write(1, exec_env->contents, ft_strlen(exec_env->contents));
		write(1, "\n", 1);
}

int	exec_env(t_env **env)
{
	t_env	*exec_env;
	int		res;
	// int		status;
	// pid_t	pid;

	res = 0;
	// if (exec_cmd->has_pip)
	// 	if (pipe(exec_cmd->fd) < 0)
	// 		exit(0);
	exec_env = *env;
	// if (!exec_cmd->has_pip)
	// {
		while (exec_env != NULL)
		{
			write_env(exec_env);
			exec_env = exec_env->next;
		}
	// }
	return (0);

}

// int exec_env(t_cmd *exec_cmd, char **env)
// {
// 	char buf[1024];

// 	if (exec_cmd->has_pip)
// 		if (pipe(exec_cmd->fd) < 0)
// 			exit(0);
// 	getcwd(buf, 1024);
// 	if(chdir(exec_cmd->cmd[1]) == -1)
// 		printf("failed, cd\n");
// 		return (0);
// }

void pre_exec_env(t_cmd *exec_cmd, pid_t *pid, t_env  **env)
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
			exit(exec_env(env));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
	}
	else
		exec_env(env);
}
