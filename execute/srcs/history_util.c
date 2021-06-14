/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:54 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/11 13:51:39 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void		add_back_his(t_history **lst, t_history *new)
{
	t_history *tmp;

	tmp = (*lst)->tail;
	tmp->tail = (*lst)->tail;
	tmp->prev->next = new;
	new->prev = tmp->prev;
	tmp->prev = new;
	new->next = tmp;
	new->head = (*lst)->head;
	new->tail = (*lst)->tail;
}

t_history	*new_his_buf(char *buf)
{
	t_history *new;

	if (!buf)
		return (0);
	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
		return (0);
	new->buf = buf;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_history	*new_his(void)
{
	t_history *new;

	new = (t_history *)malloc(sizeof(t_history));
	if (!new)
		return (0);
	new->buf = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->tail = NULL;
	return (new);
}

void		history_ht(t_history **head, t_history **tail)
{
	*head = new_his();
	*tail = new_his();
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
}
