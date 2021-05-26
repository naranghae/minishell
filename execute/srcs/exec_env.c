#include "minishell_header.h"
#include "minishell_parsing.h"

int		listlen(t_env *env_info)
{
	t_env	*envCount;
	int	i;

	i = 0;
	envCount = env_info->next;
	while (envCount != NULL)
	{
		if (envCount->equal)
			i++;
		envCount = envCount->next;
	}
	return (i);
}

int		listlenAll(t_env *env_info)
{
	t_env	*envCount;
	int	i;

	i = 0;
	envCount = env_info->next;
	while (envCount != NULL)
	{
		i++;
		envCount = envCount->next;
	}
	return (i);
}

void	write_env(t_env	*exec_env)
{
	if (exec_env->equal)
	{
		//write(1, exec_env->name, ft_strlen(exec_env->name));
		//write(1, "=", 1);
		//write(1, exec_env->contents, ft_strlen(exec_env->contents));
		//write(1, "\n", 1);
		printf("%s=%s\n", exec_env->name, exec_env->contents);
	}
}

int	exec_env(t_env *env_info)
{
	t_env	*exec_env;

	exec_env = env_info->next;
	while (exec_env != NULL)
	{
		write_env(exec_env);
		exec_env = exec_env->next;
	}
	return (0);

}

void		pre_exec_env(t_cmd *exec_cmd, pid_t *pid, t_env  *env_info)
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
			exit(exec_env(env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
	}
	else
		exec_env(env_info);
}
