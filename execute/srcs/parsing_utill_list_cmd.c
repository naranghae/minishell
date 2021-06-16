/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_list_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:54 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/15 19:22:48 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

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
	(*head)->head = (*head);
	(*head)->tail = (*tail);
	(*tail)->tail = (*tail);
	(*tail)->head = (*head);
	(*head)->tail->buf = NULL;
	p_v->start = 0;
	p_v->i = 0;
}
