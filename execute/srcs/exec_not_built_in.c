#include "minishell_header.h"
#include "minishell_parsing.h"

void	exec_not_built_in(t_cmd *exec_cmd, char **path, char **envp)
{
	pid_t	pid;
	int		res = 0;
	int		status;
	int		i;
	char	*join;
	char	*pathjoin;
	
	i = 0;
	pid = 0;
	status = 0;
	if (pipe(exec_cmd->fd) < 0)
			exit(0);
			//exit_fatal();
	pid = fork();
	if (pid < 0)
		exit(0);
		//exit_fatal();
	else if (pid == 0)
	{
		if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
			exit(0);
			//exit_fatal();
		if (exec_cmd->prev && exec_cmd->prev->has_pip && dup2(exec_cmd->prev->fd[0], 0) < 0)
			exit(0);
			//exit_fatal();
		while (path[i] != NULL)
		{
			join = ft_strjoin(path[i], "/");
			pathjoin = ft_strjoin(join, exec_cmd->cmd[0]);
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(write(1,"error\n",6) * 0);
			//if (exec_cmd->cmd && )
			res = execve(pathjoin, exec_cmd->cmd, envp);
			free(path[i]);
			free(join);
			free(pathjoin);
			i++;
		}
		exit(printf("no cmd\n") * 0 + res);
	}
	else if (pid > 0)
		close_pipe(&pid, exec_cmd, res, status);
}