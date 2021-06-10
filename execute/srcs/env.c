/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:22:34 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 15:31:07 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

t_env	*new_env(void)
{
	t_env	*lst;

	if (!(lst = (t_env *)malloc(sizeof(*lst))))
		return (NULL);
	lst->envp = NULL;
	lst->name = NULL;
	lst->contents = NULL;
	lst->equal = 0;
	lst->next = NULL;
	return (lst);
}

t_env	*last_env(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	add_back_env(t_env **lst, t_env *new)
{
	t_env *last;

	if (lst)
	{
		if (*lst)
		{
			last = last_env(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

void	save_env(t_env *env_parse, char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
		{
			env_parse->name = ft_substr(str, 0, i);
			env_parse->contents = ft_substr(str, i + 1,
				ft_strlen(str) - (i + 1));
			env_parse->next = NULL;
			env_parse->equal = 1;
			return ;
		}
	}
	env_parse->name = ft_substr(str, 0, ft_strlen(str));
	env_parse->contents = 0;
	env_parse->equal = 0;
	env_parse->next = NULL;
}

t_env	*parsing_env(char **env)
{
	t_env	*env_parse;
	t_env	*env_set;
	int		i;

	i = -1;
	env_set = new_env();
	while (env[++i] != NULL)
	{
		if (!(env_parse = (t_env *)malloc(sizeof(*env_parse))))
			return (NULL);
		save_env(env_parse, env[i], '=');
		add_back_env(&env_set, env_parse);
	}
	return (env_set);
}
