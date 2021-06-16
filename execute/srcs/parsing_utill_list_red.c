/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_list_red.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:54 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/16 16:00:44 by chanykim         ###   ########.fr       */
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
