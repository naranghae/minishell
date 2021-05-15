/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:54 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/15 19:55:09 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	add_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd *tmp;

	tmp = (*lst)->tail;
	tmp->prev->next = new;
	new->prev = tmp->prev;
	tmp->prev = new;
	new->next = tmp;
}


t_cmd	*new_cmd(char **cmd)
{
	t_cmd *new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cmd = cmd;
	new->has_pip = 0;
	new->has_red = 0;
	new->next = NULL;
	new->prev = NULL;
	new->tail = NULL;
	return (new);
}

void	init_cmd(t_cmd **head, t_cmd **tail)
{

	*head = new_cmd(NULL);
	*tail = new_cmd(NULL);
	(*head)->next = (*tail);
	(*head)->prev = (*head);
	(*tail)->next = (*tail);
	(*tail)->prev = (*head);
	(*head)->tail = (*tail);
}