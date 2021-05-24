#include "minishell_header.h"
#include "minishell_parsing.h"

int exec_echo(t_cmd *exec_cmd)
{
	if (exec_cmd->has_pip)
		if (pipe(exec_cmd->fd) < 0)
			exit(0);
	if (exec_cmd->cmd[1] == NULL)
		printf("\n");
	else if (exec_cmd->cmd[1] && !ft_strncmp(exec_cmd->cmd[1],"-n", 2))
	{
	printf ("cmp : %d s : %s\n",!ft_strncmp(exec_cmd->cmd[1],"-n ", 3), exec_cmd->cmd[1]);
		if(!ft_strncmp(exec_cmd->cmd[1],"-n ", 3))
		{
			printf("1231sdasdasdasdasdasdasd asd asdasgfadfg23%s", exec_cmd->cmd[1]);
		}
		else
			printf("");
	}
	else
		printf("%s\n", exec_cmd->cmd[1]);
	return (0);
}

void pre_exec_echo(t_cmd *exec_cmd, pid_t *pid)
{
	int status;
	int res;

	res = 0;
	status = 0;
	if (exec_cmd->has_pip)
	{
		if (pid == 0)
		{
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(0);
			if (exec_cmd->prev && exec_cmd->prev->has_pip && dup2(exec_cmd->prev->fd[0], 0) < 0)
				exit(0);
			exit(exec_echo(exec_cmd));
		}
		else if (pid > 0)
		close_pipe(pid, exec_cmd, res, status);
	}
	else
		exec_echo(exec_cmd);
}