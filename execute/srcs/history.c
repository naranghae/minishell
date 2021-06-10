/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 20:37:29 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 15:33:33 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		historylst_num(t_history *history)
{
	int		i;

	i = 0;
	history = history->tail;
	while (history->head != history->prev)
	{
		history = history->prev;
		i++;
	}
	return (i);
}

char	*history_up(t_history **cmd, t_cursor *cursor)
{
	int		len;
	char	*str;

	len = 0;
	str = NULL;
	if ((*cmd) == (*cmd)->head)
		return (NULL);
	if (cursor->c == UP_ARROW)
	{
		if ((*cmd)->buf != NULL)
			len = ft_strlen((*cmd)->buf);
		while (len--)//리스트로 과거로그를 볼 때 현재 문자열을 삭제함.
			delete_end(cursor);
		if ((*cmd)->prev != (*cmd)->head)
			(*cmd) = (*cmd)->prev;
		if((*cmd)->buf != NULL)
			print_buf(cursor, (*cmd)->buf);
		else
			return (NULL);
		str = ft_strdup((*cmd)->buf);
		return (str);
	}
	return (NULL);
}

char	*history_down(t_history **cmd, t_cursor *cursor)
{
	int		len;
	char	*str;

	len = 0;
	str = NULL;
	if ((*cmd) == (*cmd)->head)
		return (NULL);
	if (cursor->c == DOWN_ARROW)
	{
		if ((*cmd)->buf != NULL)
			len = ft_strlen((*cmd)->buf);
		while (len--)
			delete_end(cursor);
		(*cmd) = (*cmd)->next;
		if((*cmd)->buf != NULL)
			print_buf(cursor, (*cmd)->buf);
		else
			return (NULL);
		str = ft_strdup((*cmd)->buf);
		return (str);
	}
	return (NULL);
}

t_history	*init_history(void)
{
	t_history *head;
	t_history *tail;
	history_ht(&head, &tail);
	return (head);
}