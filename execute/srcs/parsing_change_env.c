/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:42:06 by hyopark           #+#    #+#             */
/*   Updated: 2021/06/15 21:02:30 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int		find_end(t_cmd *cmd, int ix, int i)
{
	int	re;

	if (cmd->cmd[ix][i] != '\0')
		i++;
	else
		return (i);
	while (cmd->cmd[ix][i] != '\0' && cmd->cmd[ix][i] != ' ' && cmd->cmd[ix][i]
		!= '$' && cmd->cmd[ix][i] != '"' && cmd->cmd[ix][i] != '\'')
		i++;
	re = i;
	return (re);
}

int		env_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (ft_strlen(s1) < n || ft_strlen(s2) < n)
		return (1);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}


char	*find_env(t_cmd *cmd, t_env *env, int ix, int *i)
{
	t_env	*tmp;
	int		end;
	int		st;
	int		max;

	max = 0;
	st = *i + 1;
	end = find_end(cmd, ix, *i);
	tmp = env->next;
	printf("%d\n", end - st + 1);
	while (tmp != NULL)
	{
			max = ft_strlen(&cmd->cmd[ix][*i]) > ft_strlen(tmp->name) ?
			ft_strlen(&cmd->cmd[ix][*i]) : ft_strlen(tmp->name);
		if (!ft_strncmp(&cmd->cmd[ix][*i], tmp->name, max))//end - st + 1))
		{
			*i += ft_strlen(tmp->name);
			return (tmp->contents);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	change_env_save(t_cmd **tmp, t_c_env *c_e, t__free_p *f_p)
{
	if (c_e->envstr != 0)
	{
		f_p->tmp1 = ft_substr((*tmp)->cmd[c_e->ix], 0, c_e->st - 1);
		f_p->tmp2 = ft_strdup(&((*tmp)->cmd[c_e->ix][c_e->i]));
		f_p->tmp3 = ft_strjoin(f_p->tmp1, c_e->envstr);
		free((*tmp)->cmd[c_e->ix]);
		(*tmp)->cmd[c_e->ix] = ft_strjoin(f_p->tmp3, f_p->tmp2);
		free(f_p->tmp1);
		free(f_p->tmp2);
		free(f_p->tmp3);
		c_e->i = (c_e->st - 1) + ft_strlen(c_e->envstr);
	}
	else
	{
		f_p->tmp1 = ft_substr((*tmp)->cmd[c_e->ix], 0, c_e->st - 1);
		f_p->tmp2 = ft_strdup(&((*tmp)->cmd[c_e->ix]
			[find_end((*tmp), c_e->ix, c_e->st)]));
		free((*tmp)->cmd[c_e->ix]);
		f_p->tmp3 = ft_strjoin(f_p->tmp1, f_p->tmp2);
		(*tmp)->cmd[c_e->ix] = f_p->tmp3;
		free(f_p->tmp1);
		free(f_p->tmp2);
		c_e->i = (c_e->st - 1);
	}
}

void	change_env(t_cmd *tmp, t_env *env, int ix, int i)
{
	t_c_env		c_env;
	t__free_p	f_p;

	c_env.ix = ix;
	c_env.i = i;
	while (tmp->cmd[c_env.ix][c_env.i] != '\0')
	{
		if (tmp->cmd[c_env.ix][c_env.i] == '\\')
		{
			if (tmp->cmd[c_env.ix][(c_env.i)++ + 1] != '\0')
				c_env.i += 1;
			continue ;
		}
		if (tmp->cmd[c_env.ix][(c_env.i)++] == '$' &&
			!in_singlequote(tmp->cmd[c_env.ix], c_env.i, 0, 0))
		{
			c_env.st = c_env.i;
			c_env.envstr = find_env(tmp, env, c_env.ix, &(c_env.i));
			change_env_save(&tmp, &c_env, &f_p);
		}
	}
}
