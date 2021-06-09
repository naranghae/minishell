/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/09 21:13:57 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		main(int argc, char **argv, char **envp)
{
	t_env		*env_info;
	t_cmd		*cmd;
	t_history	*history; //입력하고 엔터치고 저장된 문자열
	t_cursor	cursor;
	char		*hisbuf; //입력하고 있는 문자열
	char		*tmpbuf;
	int			len;

	/* init termcap */
	tgetent(NULL, "xterm");
	//init etc..
	firstWall(argc, argv);
	env_info = parsing_env(envp);
	history = init_history();
	signal_func();
	cmd = NULL;
	hisbuf = NULL;
	len = 0;
	tmpbuf = NULL;
	while (1)
	{
		prompt();
		set_termios(SET);
		init_cursor(&cursor);
		while (read(0, &cursor.c, sizeof(cursor.c)) > 0)
		{
			get_cursor_position(&cursor.col, &cursor.row);
			//ctrl + c가 들어왔을 때
			set_termios(INPUT);
			if (cursor.c == CTRLC)
			{
				if (cursor.buf != NULL)
				{
					free(cursor.buf);
					cursor.buf = NULL;
				}
				cursor.c = 0;
				write(1, "\n", 1);
				break ;
			}
			if (cursor.buf == NULL)
				cursor.buf = ft_calloc(1, sizeof(char));
			if (cursor.c == LEFT_ARROW)
				move_cursor_left(&cursor);
			else if (cursor.c == RIGHT_ARROW)
				move_cursor_right(&cursor);
			else if (cursor.c == BACKSPACE)
			{
				delete_end(&cursor);
				cursor.buf = remove_char(cursor);
				//cursor.buf에 담긴 거 하나씩 삭제.
			}
			else if ((cursor.c == UP_ARROW) && ((0 < cursor.listcircle) && (historylst_num(history) >= cursor.listcircle)))
			{
				//(head랑 tail사이에 값이 있을 때)
				if (history->head->next != history->tail)
				{
					len = ft_strlen(cursor.buf);
					while (len--)
						delete_end(&cursor);
				}
				if ((cursor.listcircle == 1) && (cursor.buf[0] != '\0'))
				{
					tmpbuf = ft_strdup(cursor.buf);
					free(cursor.buf);
					cursor.buf = NULL;
				}
				cursor.listcircle++;
				hisbuf = history_up(&history, &cursor);
				if (hisbuf != NULL) //history 올렸을 때 있는 문자열 저장
				{
					if (cursor.buf)
						free(cursor.buf);
					cursor.buf = ft_strdup(hisbuf);
					free(hisbuf);
				}
				cursor.c = 0; //flush buffer
				hisbuf = NULL;
				continue ;
			}
			else if (cursor.c == DOWN_ARROW && ((0 < cursor.listcircle) && ((historylst_num(history) + 1) >= cursor.listcircle)))
			{
				cursor.listcircle--;
				if (cursor.listcircle != 0)
				{
					if (history->head->next != history->tail)
					{
						len = ft_strlen(cursor.buf);
						while (len--)
							delete_end(&cursor);
					}
					hisbuf = history_down(&history, &cursor);
				}
				if (hisbuf != NULL) //history 올렸을 때 있는 문자열 저장
				{
					if (cursor.buf)
						free(cursor.buf);
					cursor.buf = ft_strdup(hisbuf);
					free(hisbuf);
					hisbuf = NULL;
				}
				else if (hisbuf == NULL && (cursor.listcircle == 1)) //맨 아래일 때
				{
					if (cursor.buf)
						free(cursor.buf);
					if (tmpbuf != NULL)
					{
						cursor.buf = ft_strdup(tmpbuf);
						print_buf(&cursor, cursor.buf);
						free(tmpbuf);
						tmpbuf = NULL;
					}
					else if (tmpbuf == NULL)
						cursor.buf = NULL;
				}
				if (cursor.listcircle == 0)
					cursor.listcircle = 1;
				cursor.c = 0; //flush buffer
				continue ;

			}
			else if (keyValue(cursor))
			{
				cursor.col++;
				write(0, &cursor.c, 1);
			}
			if (cursor.c != '\n' && keyValue(cursor))
				cursor.buf = append_char(cursor);
			else if (cursor.c == '\n')
			{
				history = history->tail;
				printf("나오는 버퍼: %s|\n", cursor.buf);
				if (cursor.buf[0] != '\0')
					add_back_his(&history, new_his_buf(ft_strdup(cursor.buf)));
				if (tmpbuf)
				{
					free(tmpbuf);
					tmpbuf = NULL;
				}
				cursor.c = 0; //flush buffer
				break ;
			}
			if (cursor.c == CTRLD && (cursor.buf[0] == '\0'))
			{
				cursor.c = 0;
				ctrl_d_exit();
			}
			cursor.c = 0; //flush buffer
		}
		if (cursor.c != CTRLC)
		{
			cursor.c = '\n';
			cursor.buf = append_char(cursor);
			cursor.c = 0;
			cmd = parsing_cmd(cursor.buf, env_info);
			if (cmd)
				exec(&cmd, &env_info);
			free(cursor.buf);
			cursor.buf = NULL;
		}
	}
	return (0);
}