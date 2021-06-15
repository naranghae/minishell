/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/15 16:09:54 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		enter_key(t_cursor *cursor, t_history **history)
{
	if (cursor->c != '\n' && key_value(*cursor))
		cursor->buf = append_char(*cursor);
	else if (cursor->c == '\n')
	{
		(*history) = (*history)->tail;
		if (cursor->buf[0] != '\0')
			add_back_his(history, new_his_buf(ft_strdup(cursor->buf)));
		if (cursor->tmpbuf)
		{
			free(cursor->tmpbuf);
			cursor->tmpbuf = NULL;
		}
		cursor->c = 0;
		return (1);
	}
	if (cursor->c == CTRLD && (cursor->buf[0] == '\0'))
	{
		cursor->c = 0;
		ctrl_d_exit();
	}
	cursor->c = 0;
	return (0);
}

int		ctrl_c(t_cursor *cursor)
{
	get_cursor_position(&cursor->row);
	set_termios(INPUT);
	if (cursor->c == CTRLC)
	{
		if (cursor->buf != NULL)
		{
			free(cursor->buf);
			cursor->buf = NULL;
		}
		cursor->c = 0;
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void	cursor_move(t_cursor *cursor)
{
	if (cursor->buf == NULL)
		cursor->buf = ft_calloc(1, sizeof(char));
	if (cursor->c == LEFT_ARROW)
		move_cursor_left(cursor);
	else if (cursor->c == RIGHT_ARROW)
		move_cursor_right(cursor);
	else if (cursor->c == BACKSPACE)
	{
		delete_end(cursor);
		cursor->buf = remove_char(*cursor);
	}
}

void	input_mode(t_cursor *cursor, t_history **history)
{
	while (read(0, &cursor->c, sizeof(cursor->c)) > 0)
	{
		if (ctrl_c(cursor))
			break ;
		cursor_move(cursor);
		if ((cursor->c == UP_ARROW) && ((0 < cursor->listcircle) && \
			(historylst_num((*history)) >= cursor->listcircle)))
		{
			history_past(cursor, history);
			continue ;
		}
		else if (cursor->c == DOWN_ARROW && ((0 < cursor->listcircle) && \
			((historylst_num((*history)) + 1) >= cursor->listcircle)))
		{
			history_future(cursor, history);
			continue ;
		}
		else if (key_value(*cursor))
			char_print(cursor);
		if (enter_key(cursor, history))
			break ;
	}
}

void	exec_intro(t_cursor *cursor, t_cmd *cmd, t_env *env_info)
{
	if (cursor->c != CTRLC)
	{
		cursor->c = '\n';
		cursor->buf = append_char(*cursor);
		cursor->c = 0;
		cmd = parsing_cmd(cursor->buf);
		if (cmd)
		{
			write(1, "aa\n", 3);
			exec(&cmd, &env_info);
			free_cmd(&cmd);
		}
		free(cursor->buf);
		cursor->buf = NULL;
	}
}
