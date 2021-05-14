#include "minishell_header.h"
#include "minishell_parsing.h"

/*
void	pipe_built_in(t_cmd *exec_cmd, t_env *exec_env, char **envp, int *fd)
{
	pid_t	pid;
	char	**path;
	int		i;
	char	*join;
	char	*pathjoin;

	i = 0;

	while (exec_env != NULL)
	{
		if (!ft_strncmp(exec_env->name, "PATH", 4))
			path = ft_split(exec_env->contents,':');
		exec_env = exec_env->next;
	}
	while (path[i] != NULL)
	{
		join = ft_strjoin(path[i], "/");
		pathjoin = ft_strjoin(join, exec_cmd->cmd[0]);
	}
}

void	exec_not_built_in(t_cmd *exec_cmd, t_env *exec_env, char **envp)
{
	char	**path;
	int		i;
	char	*join;
	char	*pathjoin;
	pid_t	pid;
	int		status;
	int		fd[2];

	i = 0;
	if (exec_cmd->has_pip > 0)
	{
		if (pipe(fd) < 0){
			printf("pipe error\n");
			return ;
		}
		pipe_built_in(exec_cmd, exec_env, envp, fd);
	}
	else{
		pid = fork();
		if (pid < 0)
		{
			printf("fork failed!\n");
			return ;
		}
		else if (pid == 0)
		{
			while (exec_env != NULL)
			{
				if (!ft_strncmp(exec_env->name, "PATH", 4))
					path = ft_split(exec_env->contents,':');
				exec_env = exec_env->next;
			}
			while (path[i] != NULL)
			{
				join = ft_strjoin(path[i], "/");
				pathjoin = ft_strjoin(join, exec_cmd->cmd[0]);
				execve(pathjoin, exec_cmd->cmd, envp);
				free(join);
				free(pathjoin);
				i++;
			}
			exit(write(1,"error\n",6) * 0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, WUNTRACED);
		}
	}
}
*/


void	exec_not_built_in(t_cmd *exec_cmd, char **path, char **envp)
{
	int		i;
	char	*join;
	char	*pathjoin;
	pid_t	pid;
	int		status;
	int		res;

	i = 0;
	if (exec_cmd->has_pip > 0)
	{
		if (pipe(exec_cmd->fd) < 0){
			printf("pipe error\n");
			return ;
		}
	}
	pid = fork();
	if (pid < 0)
	{
		printf("fork failed!\n");
		return ;
	}
	else if (pid == 0)
	{
		while (path[i] != NULL)
		{
			join = ft_strjoin(path[i], "/");
			pathjoin = ft_strjoin(join, exec_cmd->cmd[0]);
			if (exec_cmd->has_pip && dup2(exec_cmd->fd[1], 1) < 0)
				exit(write(1,"error\n",6) * 0);
			if (exec_cmd->cmd && )
			res = execve(pathjoin, exec_cmd->cmd, envp);
			free(path[i]);
			free(join);
			free(pathjoin);
			i++;
		}
		exit(write(1,"error\n",6) * 0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (exec_cmd->cmd)
			close(exec_cmd->fd[0]);
		if (exec_cmd->has_pip)
			close(exec_cmd->fd[1]);
	}
}

void	exec_cmd(t_cmd **cmd, t_env **env_set, char **envp)
{
	t_cmd	*exec_cmd;
	t_env	*exec_env;
	char	**path;

	exec_cmd = *cmd;
	exec_env = *env_set;
	while (exec_env != NULL)
	{
		if (!ft_strncmp(exec_env->name, "PATH", 4))
			path = ft_split(exec_env->contents,':'); //leaks
		exec_env = exec_env->next;
	}
	while (exec_cmd != NULL)
	{
		if (!ft_strncmp(exec_cmd->cmd[0], "cd", 2))
			{printf("cd\n");}
		else
			exec_not_built_in(exec_cmd, path, envp);
		exec_cmd = exec_cmd->next;
	}

}
