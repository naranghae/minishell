#include "minishell_header.h"
#include "minishell_parsing.h"

char	**getEnvp(t_env *env_set)
{
	int		i;
	int		k;
	char	*ejoin;
	char	*envjoin;
	char	**envpp;
	t_env	*envParse;

	k = 0;
	envParse = env_set->next;
	i = listlen(env_set);
	envpp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envpp)
		return (NULL);
	while (envParse != NULL)
	{
		if (envParse->contents)
		{
			ejoin = ft_strjoin(envParse->name, "=");
			envjoin = ft_strjoin(ejoin, envParse->contents);
			envpp[k++] = envjoin;
			//printf("%s\n", envpp[k - 1]);
			free(ejoin);
		}
		envParse = envParse->next;
	}
	envpp[k] = NULL;
	return (envpp);
}

void	exec_not_built_in(t_cmd *exec_cmd, char **path, char **envp)
{
	pid_t	pid;
	int		res = 0;
	int		status;
	int		i;
	char	*pjoin;
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
			pjoin = ft_strjoin(path[i], "/");
			pathjoin = ft_strjoin(pjoin, exec_cmd->cmd[0]);
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(write(1,"error\n",6) * 0);
			res = execve(pathjoin, exec_cmd->cmd, envp);
			free(path[i]);
			free(pjoin);
			free(pathjoin);
			i++;
		}
		exit(res);
	}
	else if (pid > 0)
		close_pipe(&pid, exec_cmd, res, status);
}