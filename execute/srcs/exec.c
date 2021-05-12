#include "minishell_header.h"
#include "minishell_parsing.h"
#include <string.h>

void	exec_not_built_in(t_cmd *exec_cmd, t_env *exec_env, char **envp)
{
	char **path;
	int	i;
	char *join;

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
		//printf("cat: %s\n", join);
		// if (execve(ft_strjoin(join, exec_cmd->cmd[0]), exec_cmd->cmd, envp) != -1)
		// 	return ;
		printf("0: %s$\n", exec_cmd->cmd[0]);
		printf("1: %s$\n", exec_cmd->cmd[1]);
		//printf("2: %s$\n", exec_cmd->cmd[2]);
		printf("cat: %s1\n", ft_strjoin(join, exec_cmd->cmd[0]));
		execve(ft_strjoin(join, exec_cmd->cmd[0]), exec_cmd->cmd, envp);
		i++;
	}
	exit(write(1,"error",5) * 0);
}


void	exec_cmd(t_cmd **cmd, t_env **env_set, char **envp)
{
	t_cmd	*exec_cmd;
	t_env	*exec_env;

	exec_cmd = *cmd;
	exec_env = *env_set;
	while (exec_cmd != NULL)
	{
		printf("wwww\n");
		if (!ft_strncmp(exec_cmd->cmd[0], "cd", 2))
			//exec_cd();
			//else if
			{printf("cd\n");}
		else
		{
			printf("4444");
			exec_not_built_in(exec_cmd, exec_env, envp);
		}
		exec_cmd = exec_cmd->next;
	}

}
