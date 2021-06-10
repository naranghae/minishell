/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 19:54:00 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	char_print(t_cursor *cursor)
{
	cursor->col++;
	write(0, &cursor->c, 1);
}

void	history_past(t_cursor *cursor, t_history **history)
{
	if ((*history)->head->next != (*history)->tail)
	{
		cursor->len = ft_strlen(cursor->buf);
		while (cursor->len--)
			delete_end(cursor);
	}
	if ((cursor->listcircle == 1) && (cursor->buf[0] != '\0'))
	{
		cursor->tmpbuf = ft_strdup(cursor->buf);
		free(cursor->buf);
		cursor->buf = NULL;
	}
	cursor->listcircle++;
	cursor->hisbuf = history_up(history, &cursor);
	if (cursor->hisbuf != NULL)
	{
		if (cursor->buf)
			free(cursor->buf);
		cursor->buf = ft_strdup(cursor->hisbuf);
		free(cursor->hisbuf);
	}
	cursor->c = 0;
	cursor->hisbuf = NULL;
}

void	history_future(t_cursor *cursor, t_history **history)
{
	search_future(cursor, history);
	if (cursor->hisbuf != NULL)
	{
		if (cursor->buf)
			free(cursor->buf);
		cursor->buf = ft_strdup(cursor->hisbuf);
		free(cursor->hisbuf);
		cursor->hisbuf = NULL;
	}
	else if (cursor->hisbuf == NULL && (cursor->listcircle == 1))
		now_input(cursor);
	if (cursor->listcircle == 0)
		cursor->listcircle = 1;
	cursor->c = 0;
}

void	search_future(t_cursor *cursor, t_history **history)
{
	cursor->listcircle--;
	if (cursor->listcircle != 0)
	{
		if ((*history)->head->next != (*history)->tail)
		{
			cursor->len = ft_strlen(cursor->buf);
			while (cursor->len--)
				delete_end(cursor);
		}
		cursor->hisbuf = history_down(history, &cursor);
	}
}

void	now_input(t_cursor *cursor)
{
		if (cursor->buf)
			free(cursor->buf);
		if (cursor->tmpbuf != NULL)
		{
			cursor->buf = ft_strdup(cursor->tmpbuf);
			print_buf(&cursor, cursor->buf);
			free(cursor->tmpbuf);
			cursor->tmpbuf = NULL;
		}
		else if (cursor->tmpbuf == NULL)
			cursor->buf = NULL;
}
