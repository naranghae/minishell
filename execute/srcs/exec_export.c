/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/24 20:42:31 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

/*
int		exceptName(int str, int i)
{
	if ((i == 0) && (ft_isalpha(str) < 1) && (str != '_'))
		return (1);
	else if ((i == 1) && (ft_isalpha(str) < 1) && (str != '_') && (str != '$') && ft_isdigit(str))
		return (1);
	return (0);
}

int		exceptContents(int str, int i)
{
	if ((i == 0) && (ft_isalpha(str) < 1) && (str != '_') && (str != '$') && ft_isdigit(str))
		return (1);
	else if ((i > 0) && (ft_isalpha(str) < 1) && (str != '_') && (str != '$') && ft_isdigit(str))
		return (1);
	return (0);
}

void	cmdError(t_env *env_info, char *cmd, int *error, int idx)
{
	*error = 1;
	int		i;

	i = -1;
	if ((idx == 0))
		while (cmd[++i] != NULL)
		{
			if(cmd[i] == '=')
			{
				printf("export: '%s' : not a valid identifier\n", cmd + i);
				return ;
			}
		}
	else if ((idx == 0) && ft_isdigit(cmd[idx]))
	{
		printf("export: '%s' : not a valid identifier\n", cmd + i);
				return ;
	}

}

int		exceptCheck(char *exportCmd, t_env *env_info)
{
	char	*exceptCmd;
	int		i;
	int		error;

	i = -1;
	error = 0;
	if (exceptDollar(exportCmd, env_info))
		return (1);
	while (exceptCmd[++i] != '\0')
	{
		if (exceptName(exceptCmd[i], i))
			cmdError(env_info, exceptCmd[i], &error, i);
	}
	if (error != 0)
		return (1);
	else
		return (0);
}
*/
int		equalIs(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == '=')
			return (1);
	}
	return (0);
}

int		nameSearch(t_env *env_parse, t_env *env_info)
{
	t_env	*exec_env;
	char	*contents;

	contents = NULL;
	exec_env = env_info;
	while (exec_env != NULL)
	{
		if (!ft_strncmp(env_parse->name, exec_env->name, ft_strlen(exec_env->name)))
		{
			contents = ft_strdup(env_parse->contents);
			exec_env->contents = contents;
			return (1);
		}
		exec_env = exec_env->next;
	}

	return (0);
}

int		envAdd(char *cmd, t_env *env_info)
{
	int		i;
	t_env	*env_parse;

	i = -1;

	if (equalIs(cmd))
	{
		if(!(env_parse = (t_env *)malloc(sizeof(*env_parse))))
			return (0);
		save_env(env_parse, cmd, '=');
		if (nameSearch(env_parse, env_info))
		{
			free(env_parse->name);
			free(env_parse->contents);
			free(env_parse);
			return (0);
		}
		else
			add_back_env(&env_info, env_parse);
	}
	return (0);
}

int		parsingEnv(char *cmd, t_env *env_info)
{
	char			*tmp;
	char			**exportCmd;
	int				i;

	i = -1;
	tmp = cmd;
	exportCmd = ft_split(tmp, ' ');
	while (exportCmd[++i] != NULL)
	{
		//if (exceptCheck(exportCmd[i], env_info))
		//	return (1);
		//else
		{
			envAdd(exportCmd[i], env_info);
			return (0);
		}
	}
	return (0);
}

void	swapList(t_env *env, t_env *envNext)
{
	char	*tmpName;
	char	*tmpContents;

	tmpName = env->name;
	env->name = envNext->name;
	envNext->name = tmpName;
	tmpContents = env->contents;
	env->contents = envNext->contents;
	envNext->contents = tmpContents;
}

void	envSort_print(t_env *env_info)
{
	t_env	*envSort;
	int		listNum;
	int		i;
	int		j;

	i = -1;
	j = -1;
	envSort = env_info;
	listNum = listlen(&envSort);
	while (++i < listNum)
	{
		if (envSort->next == NULL)
			break ;
		while (++j < listNum - 1 - i)
		{
			//printf("%s\n", envSort->name);
			//printf("%s\n", envSort->next->name);
			if (ft_strncmp(envSort->name, envSort->next->name, ft_strlen(envSort->name)) > 0)
				swapList(envSort, envSort->next);
			envSort = envSort->next;
		}
		j = -1;
		envSort = env_info->next;
	}
	while (env_info != NULL)
	{
		if (env_info->contents != NULL)
			printf("declare -x %s\n", env_info->name);
		printf("declare -x %s=\"%s\"\n", env_info->name, env_info->contents);
		env_info = env_info->next;
	}
}

int		exec_export(t_cmd *exec_cmd, t_env *env_info)
{
	t_env	*envPrint;

	envPrint = env_info;
	if (exec_cmd->cmd[1] == NULL)
	{
		envSort_print(envPrint);
		return (0);
	}
	if ((exec_cmd->cmd[1] != NULL) && exec_cmd->has_pip)
		return (1);
	//exit (1); //광범위한 일반적 에러

	// export A=B | grep a 할 때 아무일도 일어나지 않음 (1 에러)
	// export | grep a 라고 하면 정렬된 env내용에서 a문자를 포함한 것이 출력됨 declare -x SHELL="/bin/zsh" declare -x A="" 이런 형식
	if (parsingEnv(exec_cmd->cmd[1], env_info))
		return (0);
	return (0);
}

void	pre_exec_export(t_cmd *exec_cmd, pid_t *pid, t_env *env_info)
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
			exit(exec_export(exec_cmd, env_info));
		}
		else if (*pid > 0)
			close_pipe(pid, exec_cmd, res, status);
	}
	else
		exec_export(exec_cmd, env_info);
}
