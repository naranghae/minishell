/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/09 19:29:42 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	ctrl_d_exit(void)
{
	write(1, "  \b\b\n", 5);
	ft_exit(g_errcode);
}

char	*append_char(t_cursor cursor)
{
	const int len = ft_strlen(cursor.buf);
	char *const	ret = ft_calloc(len + 2, 1);

	ft_memcpy(ret, cursor.buf, len);
	ret[len] = cursor.c;
	ret[len + 1] = 0;
	// printf("append: %s\n", ret);
	if (cursor.buf)
		free(cursor.buf);
	return (ret);
}

char	*remove_char(t_cursor cursor)
{
	int		len;
	char	*ret;

	len = ft_strlen(cursor.buf);
	//printf("\n remove: %s,  %d\n", cursor.buf, len);
	if (len == 0)
		return (cursor.buf);
	if (len != 0)
	{
		ret = ft_calloc(len, 1);
		ft_memcpy(ret, cursor.buf, len);
		ret[len - 1] = 0;
		if (cursor.buf)
			free(cursor.buf);
		return (ret);
	}
	return (cursor.buf);
}

// char	*remove_char(t_cursor cursor)
// {
// 	int		len;
// //	char	*ret;

// 	len = ft_strlen(cursor.buf);
// 	//printf("\n remove: %s,  %d  d:%d \n", cursor.buf, len, cursor.buf[len]);
// 	len = (len == 0) ? 1 : len;
// 	if (cursor.buf[len - 1] == '\n')
// 		cursor.buf[--len] = '\0';
// 	if (len != 0)
// 		cursor.buf[len - 1] = 0;
// 	return (cursor.buf);
// }

int		historylst_num(t_cmd *history)
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

int		nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	if (*col>-1)
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
			{
				temp = ft_atoi(&buf[i]);
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
	// *col = 14;
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_cursor_left(t_cursor *cursor)
{
	if (cursor->col > 14)
		--(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
}

void	move_cursor_right(t_cursor *cursor)
{
	int		len;

	len = ft_strlen(cursor->buf);
	//printf("%d\n", len);
	//printf("%s\n", cursor->buf);
	if ((cursor->col) <= (len + 13))
		++(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
}

void	delete_end(t_cursor *cursor)
{
	if (cursor->col > 14)
		--(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}

void	firstWall(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		write(1, "Just execute ./minishell\n", 26);
		exit(1);
	}
}

void	init_cursor(t_cursor	*cursor)
{
	cursor->buf = NULL;
	cursor->cm = tgetstr("cm", NULL); //cursor motion
	cursor->ce = tgetstr("ce", NULL); //clear line from cursor
	cursor->c = 0;
	cursor->col = 14;
	cursor->has_buf = 0;
}

// void	globalVariable(void)
// {
// 	g_gv.child = 0;
// 	g_gv.errcode = 1;
// 	g_gv.buffer = 0;
// }

char	*historyCmd(t_cmd **cmd, t_cursor *cursor)
{
	int		len;
	char	*str;

	len = 0;
	str = NULL;
	// printf("\np1:%p p2:%p p3:%p\n", cmd, *cmd, (*cmd)->next);
	if ((*cmd) == (*cmd)->head)
		return (NULL);
	// if((*cmd) == (*cmd)->tail && cursor->has_buf != 1)///////// 널조건빼고 안에서 널일경우엔 어캐할지 고민
	// {
	// 	cursor->has_buf = 1;
	// 	// printf("buf0:%d\n",cursor->buf[0]);
	// 	cursor->buf = ft_strjoin(cursor->buf, "\n");
	// 	add_back_cmd(&(*cmd)->head, new_cmd_buf(ft_strdup(cursor->buf)));
	// 	// printf("%s1\n",cursor->buf);
	// 	(*cmd)=(*cmd)->tail->prev;
	// }
		// printf("\np1:%p p2:%p p3:%p\n", cmd, *cmd, (*cmd)->next);
	if (cursor->c == UP_ARROW)
	{
		// if ((*cmd)->prev == (*cmd)->tail->head)// 147넣거나 살리거나 이 줄 살리면 터지고 안살리면 오류고
		// 	return ((*cmd)->buf);
		// else
		{
			if ((*cmd)->buf != NULL)
				len = ft_strlen((*cmd)->buf);
			while (len--)//리스트로 과거로그를 볼 때 현재 문자열을 삭제함.
				delete_end(cursor);
			if ((*cmd)->prev != (*cmd)->head)
				(*cmd) = (*cmd)->prev;
			if((*cmd)->buf != NULL)
				write(0, (*cmd)->buf, ft_strlen((*cmd)->buf));
			else
				return (NULL);
			cursor->col += (ft_strlen((*cmd)->buf));
			str = ft_strdup((*cmd)->buf);
			// if (cursor->has_buf)
			// 	remove_back_cmd(&(*cmd)->head);
			return (str);
		}
	}
	else if (cursor->c == DOWN_ARROW)
	{
		// if ((*cmd)->next == (*cmd)->tail && cursor->first_lis)
		// 	return ((*cmd)->buf);
		// else
		{
			//printf("buf: %s\n", cursor->buf);
			if ((*cmd)->buf != NULL)
				len = ft_strlen((*cmd)->buf);
			while (len--)//리스트로 과거로그를 볼 때 현재 문자열을 삭제함.
				delete_end(cursor);
			(*cmd) = (*cmd)->next;
			if((*cmd)->buf != NULL)
				write(0, (*cmd)->buf, ft_strlen((*cmd)->buf));
			else
				return (NULL);
			cursor->col += (ft_strlen((*cmd)->buf));
			str = ft_strdup((*cmd)->buf);
			// if (cursor->has_buf)
			// 	remove_back_cmd(&(*cmd)->head);// 엔터치는순간에 없애줘야할듯  없애고 커서버프에있는걸 리스트추가해야할듯
			// printf("str%d,%d\n",str[0],str[1]);
			return (str);
		}
	}
	return (NULL);
}
t_cmd	*initHistory(void)
{
	t_cmd *head;
	t_cmd *tail;
	init_cmd(&head, &tail);
	return (head);
}

int		keyValue(t_cursor cursor)
{
	if (cursor.c == LEFT_ARROW || cursor.c == RIGHT_ARROW || cursor.c == BACKSPACE ||
		cursor.c == UP_ARROW || cursor.c == DOWN_ARROW || cursor.c == CTRLD)
		return (0);
	return (1);
}

void	termios_set(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_cc[VINTR] = 3;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int		main(int argc, char **argv, char **envp)
{
	t_env		*env_info;
	t_cmd		*cmd;
	t_cmd		*history; //입력하고 엔터치고 저장된 문자열
	t_cursor	cursor;
	char		*hisbuf; //입력하고 있는 문자열
	char		*tmpbuf;
	int			len;
	int			flag;


	/* init termcap */
	tgetent(NULL, "xterm");
	//init etc..
	firstWall(argc, argv);
	env_info = parsing_env(envp);
	history = initHistory();
	signal_func();
	cmd = NULL;
	hisbuf = NULL;
	flag = 1;
	len = 0;
	tmpbuf = NULL;
	while (1)
	{
		prompt();
		//globalVariable();
		set_termios(SET);
		init_cursor(&cursor);
		while (read(0, &cursor.c, sizeof(cursor.c)) > 0)
		{
			len = historylst_num(history);
			get_cursor_position(&cursor.col, &cursor.row);
			//ctrl + c가 들어왔을 때
			set_termios(INPUT);
			if (cursor.c == CTRLC)
			{
				//write(1, " ", 1);
				if (cursor.buf != NULL)
				{
				//	len = ft_strlen(cursor.buf);
				//	while (len--)//리스트로 과거로그를 볼 때 현재 문자열을 삭제함.
				//		delete_end(&cursor);
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
			else if (cursor.c == UP_ARROW ||cursor.c == DOWN_ARROW)
			{
				//(head랑 tail사이에 값이 있을 때)
				if (history->head->next != history->tail)
				{
					len = ft_strlen(cursor.buf);
					while (len--)
						delete_end(&cursor);
				}
				if ((cursor.buf[0] != '\0') && (flag == 1) &&
					(history->head->next != history->tail))
				{
					tmpbuf = ft_strdup(cursor.buf);
					free(cursor.buf);
					cursor.buf = NULL;
					flag = 0;
				}
				hisbuf = historyCmd(&history, &cursor);
				if (hisbuf != NULL) //history 올렸을 때 있는 문자열 저장
				{
					if (cursor.buf)
						free(cursor.buf);
					cursor.buf = ft_strdup(hisbuf);
					//printf("원래 문자열 저장했니? %s\n", cursor.buf);
					flag = 0;
					free(hisbuf);
					hisbuf = NULL;
				}
				else if (hisbuf == NULL && (history->head->next != history->tail))
				{
					if (cursor.buf)
						free(cursor.buf);
					if (tmpbuf != NULL)
					{
						len = 0;
						cursor.buf = ft_strdup(tmpbuf);
						while (cursor.buf[len])
						{
							cursor.col++;
							write(1, &cursor.buf[len++], 1);
						}
						len = 0;
					}
					else
					{
						free(tmpbuf);
						tmpbuf = NULL;
						cursor.buf = NULL;
					}
				}
				cursor.c = 0; //flush buffer
				//hisbuf = NULL;
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
				{
					printf("버퍼 왜 들어와?\n");
					add_back_cmd(&history, new_cmd_buf(ft_strdup(cursor.buf)));
				}
				//free(cursor.buf);
				flag = 1;
				if (tmpbuf)
				{
					free(tmpbuf);
					tmpbuf = NULL;
				}
				//cursor.buf = NULL;
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
		// if (cursor.has_buf == 1)
		// {
		// 	cursor.has_buf = 0;
			//remove_back_cmd(&history->tail->head);
			// if (cursor.buf[0] == '\n')
			// {
			// 	tmpBuf = ft_strdup(cursor.buf + 1);
			// 	free(cursor.buf);
			// 	cursor.buf = tmpBuf;
			// }
		//}
		// if (cursor.buf[0] == '\n' && cursor.buf[1] == '\0')
		// {
		// 	free(cursor.buf);
		// 	cursor.buf = NULL;
		// 	history = history->tail;
		// 	continue ;
		// }
		//if (cursor.buf[0] != '\n' || (cursor.buf[0] == '\n' && ))
		if (cursor.c != CTRLC)
		{
			cursor.c = '\n';
			cursor.buf = append_char(cursor);
			cursor.c = 0;
			//add_back_cmd(&history, new_cmd_buf(ft_strdup(cursor.buf)));
			cmd = parsing_cmd(cursor.buf, env_info);
			//cmd->tail->prev->buf = ft_strdup(cursor.buf);
			//hisbuf = NULL;
			if (cmd)
				exec(&cmd, &env_info);
			free(cursor.buf);
			cursor.buf = NULL;
		}
	}
/*
	while (1)
	{
		prompt();
		globalVariable();
		buf = typingRead();
		cmd = parsing_cmd(buf, env_info);
		if (!cmd)
			continue ;
		exec(&cmd, &env_info);
	}
*/
	return (0);
}