/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:54 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 14:20:55 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

t_red	*last_red(t_red *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	remove_back_cmd(t_cmd **lst)
{
	t_cmd *tmp;

	tmp = (*lst)->tail;
	if (tmp->prev != tmp->head)
	{
		tmp->prev = tmp->prev->prev;
		tmp->next = tmp->tail;
	}
}

void	add_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd *tmp;

	tmp = (*lst)->tail;
	tmp->tail = (*lst)->tail;
	tmp->prev->next = new;
	new->prev = tmp->prev;
	tmp->prev = new;
	new->next = tmp;
	new->head = (*lst)->head;
	new->tail = (*lst)->tail;
}

void	add_back_red(t_red **lst, t_red *new)
{
	t_red *last;

	if (lst)
	{
		if (*lst)
		{
			last = last_red(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_red	*new_red(char *file_name, int type)
{
	t_red *new;

	new = (t_red *)malloc(sizeof(t_red));
	if (!new)
		return (0);
	new->file_name = file_name;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_cmd	*new_cmd_buf(char *buf)
{
	t_cmd *new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (0);
	new->cmd = 0;
	new->buf = buf;
	new->has_pip = 0;
	new->red = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmd	*new_cmd(char **cmd)
{
	t_cmd *new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cmd = cmd;
	new->has_pip = 0;
	new->red = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->tail = NULL;
	return (new);
}

void	init_cmd(t_cmd **head, t_cmd **tail, t_p_c *p_v)
{
	*head = new_cmd(NULL);
	*tail = new_cmd(NULL);
	(*head)->buf = NULL;
	(*head)->next = (*tail);
	(*head)->prev = (*head);
	(*tail)->next = (*tail);
	(*tail)->prev = (*head);
	(*head)->tail = (*tail);
	(*tail)->tail = (*tail);
	(*tail)->head = (*head);
	(*head)->tail->buf = NULL;
	p_v->start = 0;
	p_v->i = 0;
}
