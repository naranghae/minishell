/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:42:06 by hyopark           #+#    #+#             */
/*   Updated: 2021/06/10 14:29:26 by hyopark          ###   ########.fr       */
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

char	*find_env(t_cmd *cmd, t_env *env, int ix, int *i)
{
	t_env	*tmp;
	int		end;
	int		st;

	st = *i + 1;
	end = find_end(cmd, ix, *i);
	tmp = env->next;
	while (tmp != NULL)
	{
		if (!ft_strncmp(&cmd->cmd[ix][*i], tmp->name, end - st + 1))
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

void	init_c_env(t_c_env *c_env, int ix, int i)
{
	c_env->ix = ix;
	c_env->i = i;
}

void	change_env(t_cmd *tmp, t_env *env, int ix, int i)
{
	t_c_env		c_env;
	t__free_p	f_p;

	init_c_env(&c_env, ix, i);
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

void	init_e(t_ecs *e, t_cmd **cmd, int *ix)
{
	e->tmp = *cmd;
	e->re_i = 0;
	e->re = e->tmp->cmd[*ix];
}

void	change_escape(t_cmd **cmd, int ix, int st)
{
	t_ecs	e;

	init_e(&e, cmd, &ix);
	while (e.tmp->cmd[ix][st] != '\0')
	{
		if (e.tmp->cmd[ix][st] == '\\')
		{
			if (e.tmp->cmd[ix][st + 1] != '\0' && (e.tmp->cmd[ix][st + 1] == '`'
				|| e.tmp->cmd[ix][st + 1] == '$' || e.tmp->cmd[ix][st + 1]
					== '"' || e.tmp->cmd[ix][st + 1] == '\\'))
			{
				e.re[e.re_i++] = e.tmp->cmd[ix][st + 1];
				st += 2;
			}
			else
				e.re[e.re_i++] = e.tmp->cmd[ix][st++];
			continue ;
		}
		else
			e.re[e.re_i++] = e.tmp->cmd[ix][st];
		st++;
	}
	e.re[e.re_i] = '\0';
	(*cmd)->cmd[ix] = e.re;
}

void	change_double_qute_save(t_cmd **tmp, int *ix, int *i, t_st_end *st_end)
{
	char	*free_p;

	st_end->end = *i;
	(*tmp)->cmd[*ix][st_end->end] = '\0';
	free_p = ft_strjoin((*tmp)->cmd[*ix] + st_end->st,
		(*tmp)->cmd[*ix] + st_end->end + *ix);
	free((*tmp)->cmd[*ix]);
	(*tmp)->cmd[*ix] = ft_strjoin((*tmp)->cmd[*ix], free_p);
	free(free_p);
	*i = st_end->end - 1;
}

void	change_double_qute_init(t_cmd **tmp, int *ix, int *i, t_st_end *st_end)
{
	(*tmp)->cmd[*ix][(*i)++] = '\0';
	st_end->st = *i;
	while ((*tmp)->cmd[*ix][*i] != '\0' && (*tmp)->cmd[*ix][*i] != '\"')
		(*i)++;
}

void	change_double_qute(t_cmd *tmp, int ix, int i, t_st_end *st_end)
{
	while (tmp->cmd[ix][i] != '\0')
	{
		if (!in_doublequote(tmp->cmd[ix], i, 0, 0) && tmp->cmd[ix][i] == '\'')
			i = change_single_qute(tmp, ix, i) - 1;
		if (tmp->cmd[ix][i] == '\0')
			break ;
		if (!in_singlequote(tmp->cmd[ix], i, 0, 0) && tmp->cmd[ix][i] == '\"')
		{
			change_double_qute_init(&tmp, &ix, &i, st_end);
			if (tmp->cmd[ix][i] == '\0' && st_end->st == i)
			{
				tmp->cmd[ix][i - 1] = '"';
				return ;
			}
			if (tmp->cmd[ix][i] != '\0')
			{
				change_double_qute_save(&tmp, &ix, &i, st_end);
				continue ;
			}
			else
				break ;
		}
		i++;
	}
}

int		change_single_qute_if(t_cmd **tmp, int *ix, int *i, t_st_end *st_end)
{
	char	*free_p1;
	char	*free_p2;

	if ((*tmp)->cmd[*ix][*i] != '\0')
	{
		st_end->end = *i;
		(*tmp)->cmd[*ix][st_end->end] = '\0';
		free_p1 = ft_strjoin((*tmp)->cmd[*ix] + st_end->st,
			(*tmp)->cmd[*ix] + st_end->end + *ix);
		free_p2 = ft_strjoin((*tmp)->cmd[*ix], free_p1);
		free((*tmp)->cmd[*ix]);
		(*tmp)->cmd[*ix] = free_p2;
		free(free_p1);
		*i = st_end->end - 1;
		return (st_end->end);
	}
	else
	{
		(*tmp)->cmd[*ix][st_end->st - 1] = '\'';
		return (*i);
	}
}

int		change_single_qute(t_cmd *tmp, int ix, int i)
{
	t_st_end st_end;

	while (tmp->cmd[ix][i] != '\0')
	{
		if ((tmp->cmd[ix][i] == '\'' && tmp->cmd[ix][i + 1] != '\0'))
		{
			tmp->cmd[ix][i++] = '\0';
			if (i > 1 && tmp->cmd[ix][i - 2] == '\\')
			{
				tmp->cmd[ix][i - 2] = '\'';
				break ;
			}
			st_end.st = i;
			while (tmp->cmd[ix][i] != '\0' && tmp->cmd[ix][i] != '\'')
				i++;
			return (change_single_qute_if(&tmp, &ix, &i, &st_end));
		}
		i++;
	}
	return (i);
}

void	env_remove(char *key, t_env **env)
{
	t_env	*env_remove;
	t_env	*env_tmp;
	int		max;

	max = 0;
	env_remove = NULL;
	env_tmp = NULL;
	while ((*env)->next != NULL)
	{
		env_remove = (*env)->next;
		max = ft_strlen(key) > ft_strlen(env_remove->name) ?\
			ft_strlen(key) : ft_strlen(env_remove->name);
		if (!ft_strncmp(key, env_remove->name, max))
		{
			env_tmp = env_remove->next;
			(*env)->next = env_tmp;
			free(env_remove->name);
			if (env_remove->contents)
				free(env_remove->contents);
			free(env_remove);
			return ;
		}
		(*env) = (*env)->next;
	}
}

void	init_errorcode(t_env **errorcode)
{
	(*errorcode) = new_env();
	(*errorcode)->contents = ft_itoa(g_gv.errcode);
	(*errorcode)->name = ft_strdup("?");
}

void	change_qute(t_cmd **list, t_env *env, int i)
{
	int			ix;
	t_cmd		*tmp;
	t_env		*errorcode;
	t_st_end	st_end;

	errorcode = NULL;
	init_errorcode(&errorcode);
	tmp = *list;
	add_back_env(&env, errorcode);
	while (tmp != tmp->tail)
	{
		ix = 0;
		while (tmp->cmd[ix] != NULL)
		{
			if (ix == 0 && !ft_strncmp(tmp->cmd[ix], "$?", 2))
				break ;
			i = 0;
			change_env(tmp, env, ix, i);
			change_double_qute(tmp, ix, i, &st_end);
			change_escape(&tmp, ix, i);
			ix++;
		}
		tmp = tmp->next;
	}
	env_remove(errorcode->name, &env);
}
