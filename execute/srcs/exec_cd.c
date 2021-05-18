#include "minishell_header.h"
#include "minishell_parsing.h"

int exec_cd(t_cmd *exec_cmd)
{
	char buf[1024];

	if (exec_cmd->has_pip)
		if (pipe(exec_cmd->fd) < 0)
			exit(0);
	getcwd(buf, 1024);
	if(chdir(exec_cmd->cmd[1]) == -1)
		printf("failed, cd\n");
		return (0);
}

void pre_exec_cd(t_cmd *exec_cmd, pid_t pid)
{
	int status;
	int res;
	
	if (exec_cmd->has_pip)
	{
		if (pid == 0)
		{
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(0);
			if (exec_cmd->prev && exec_cmd->prev->has_pip && dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(0);
			exit(exec_cd(exec_cmd));
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				res = WEXITSTATUS(status);
			if (exec_cmd->has_pip)
			{
				close(exec_cmd->fd[1]);
				if (!exec_cmd->next)
					close(exec_cmd->fd[0]);
			}
			if (exec_cmd->prev && exec_cmd->prev->has_pip)
				close(exec_cmd->prev->fd[0]);
		}
	}
	else
		exec_cd(exec_cmd);
}