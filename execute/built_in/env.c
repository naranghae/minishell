/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:22:34 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 13:25:55 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_header.h"

t_env	*lstenv_new(void)
{
	t_env *lst;

	if (!(lst = (t_env *)malloc(sizeof(*lst))))
		return (NULL);
	lst->name = NULL;
	lst->contents = NULL;
	lst->next = NULL;
	return (lst);
}

t_env		*lstenv_last(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	lstenv_add_back(t_env **lst, t_env *new)
{
	t_env *last;

	if (lst)
	{
		if (*lst)
		{
			last = lstenv_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

void	env_print(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
}

void	ft_strdual_save(t_env *env_parse, char *str, int c)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
		{
			env_parse->name = ft_substr(str, 0, i);
			env_parse->contents = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
			env_parse->next = NULL;
			printf("%s = %s\n", env_parse->name, env_parse->contents);
		}
	}
}

t_env	*parsing_env(char **env)
{
	t_env	*env_parse;
	t_env	*env_set;
	int		i;

	i = -1;
	env_set = lstenv_new();
	while (env[++i] != NULL)
	{
		if(!(env_parse = (t_env *)malloc(sizeof(*env_parse))))
			return (NULL);
		ft_strdual_save(env_parse, env[i], '=');
		lstenv_add_back(&env_set, env_parse);
	}
	return (env_set);
}
