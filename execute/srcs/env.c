/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:22:34 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/18 19:16:37 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
}

void	save_env(t_env *env_parse, char *str, int c)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
		{
			env_parse->name = ft_substr(str, 0, i);
			env_parse->contents = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
			//printf("%s = %s\n", env_parse->name, env_parse->contents);
		}
	}
}

t_envlist		*parsing_env(char **env)
{
	t_envlist	*env_info;
	t_env		*env_parse;
	int			i;

	i = -1;
	if (!(env_info = (t_envlist *)malloc(sizeof(*env_info))))
		return (NULL);
	env_info->envp = env;
	env_info->env = NULL;
	while (env[++i] != NULL)
	{
		if(!(env_parse = (t_env *)malloc(sizeof(*env_parse))))
			return (NULL);
		save_env(env_parse, env[i], '=');
		ft_lstadd_back(&(env_info->env), ft_lstnew(env_parse));
	}
	return (env_info);
}
