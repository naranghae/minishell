/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/04 16:30:19 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"


void	ctrl_d_exit(void)
{
	write(1, "  \b\b\n", 5);
	ft_exit(g_gv.errcode);
}

char	*append_char(t_cursor cursor)
{
	const int len = ft_strlen(cursor.buf);
	char *const	ret = ft_calloc(len + 2, 1);

	ft_memcpy(ret, cursor.buf, len);
	ret[len] = cursor.c;
	ret[len + 1] = 0;
	if (cursor.buf)
		free(cursor.buf);
	return (ret);
}

int	nbr_length(int n)
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
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_cursor_left(t_cursor *cursor)
{
	if (cursor->col == 0)
		return ;
	--(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);

}

void	move_cursor_right(t_cursor *cursor)
{
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

void	initCursor(t_cursor	*cursor)
{
	cursor->buf = NULL;
	cursor->cm = tgetstr("cm", NULL); //cursor motion
	cursor->ce = tgetstr("ce", NULL); //clear line from cursor
	cursor->c = 0;
}

void	globalVariable(void)
{
	g_gv.child = 0;
	g_gv.errcode = 1;
}

char	*historyCmd(t_cmd **cmd, t_cursor *cursor)
{
	int		len;
	char	*str;
	int		has_buf;

	len = 0;
	has_buf = 0;
	if ((*cmd) == (*cmd)->head)
		return (NULL);
	if((*cmd) == (*cmd)->tail)
	{
		has_buf = 1;
		// add_back_cmd(&(*cmd)->head, new_cmd_buf(ft_strdup(cursor->buf)));
		// (*cmd)=(*cmd)->tail->prev;
	}
	if (cursor->c == UP_ARROW)
	{
		if ((*cmd)->prev == (*cmd)->tail->head)
			{
			printf("1\n");
			return ((*cmd)->buf);
			}
			// return (NULL);
		else
		{
			if ((*cmd)->buf != NULL)
				len = ft_strlen((*cmd)->buf);
			while (len--)
				delete_end(cursor);
			(*cmd) = (*cmd)->prev;
			write(0, (*cmd)->buf, ft_strlen((*cmd)->buf) - 1);
			str = ft_strdup((*cmd)->buf);
			len = ft_strlen(str);
			// while (len--)
			// 		cursor->col++;
			return (str);
		}
	}
	else if (cursor->c == DOWN_ARROW)
	{
		// printf("4\n");
		if ((*cmd)->next == (*cmd)->tail)
		{
			printf("1\n");
			return ((*cmd)->buf);
		}
		else
		{
			// printf("3\n");
			if ((*cmd)->buf != NULL)
				len = ft_strlen((*cmd)->buf);
			while (len--)
				delete_end(cursor);
			(*cmd) = (*cmd)->next;
			write(0, (*cmd)->buf, ft_strlen((*cmd)->buf) - 1);
			str = ft_strdup((*cmd)->buf);
			// printf("2\n");
			return (str);
		}
	}
	if (has_buf)
	{
		// emove_back_cmd(&(*cmd)->head);
	}
	// else if (cursor->c == DOWN_ARROW)
	// {
	// 	if (cmd->tail->next == cmd->tail)
	// 		return ;
	// 	else
	// 		write(1, cmd->tail->buf, ft_strlen(cmd->tail->buf));
	// }
	return (NULL);
}

t_cmd	*initHistory(void)
{
	t_cmd *head;
	t_cmd *tail;

	init_cmd(&head, &tail);
	return (head);
}

int		main(int argc, char **argv, char **envp)
{
	t_env		*env_info;
	t_cmd		*cmd;
	t_cmd		*history;
	t_cursor	cursor;
	char		*hisbuf;
	int			len;
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	/* init termcap */
	tgetent(NULL, "xterm");

	//init etc..
	initCursor(&cursor);
	firstWall(argc, argv);
	env_info = parsing_env(envp);
	history = initHistory();
	signal_func();
	hisbuf = NULL;
	cmd = NULL;

	while (1)
	{
		prompt();
		globalVariable();
		
			get_cursor_position(&cursor.col, &cursor.row);
			cursor.col = 14;
			// printf("col:%d\n",cursor.col);
		while (read(0, &cursor.c, sizeof(cursor.c)) > 0)
		{
			if (cursor.buf == NULL)
				cursor.buf = ft_calloc(1, sizeof(char));
			if (cursor.c == LEFT_ARROW)
				move_cursor_left(&cursor);
			else if (cursor.c == RIGHT_ARROW)
				move_cursor_right(&cursor);
			else if (cursor.c == BACKSPACE)
				delete_end(&cursor);
			else if (cursor.c == UP_ARROW ||cursor.c == DOWN_ARROW) // 위로 올리면 현재거 저장. 아래는 상관 X
			{
				len = ft_strlen(cursor.buf);
				while (len--)
					delete_end(&cursor);
				hisbuf = historyCmd(&history, &cursor);
				if(hisbuf)
				len = ft_strlen(hisbuf);
				while (len--)
					cursor.col++;
				cursor.c = 0; //flush buffer
				continue ;
			}
			else
			{
				cursor.col++;
				write(0, &cursor.c, 1);
			}
			if (hisbuf != NULL)// 맨끝처리 널로할지 맨끝으로할지에따라 달라짐
				cursor.buf = ft_strdup(hisbuf);
			else
				cursor.buf = append_char(cursor);
			if (cursor.c == '\n')
			{
				history = history->tail;
				cursor.c = 0; //flush buffer
				break ;
			}
			cursor.c = 0; //flush buffer
			if (cursor.buf[0] == CTRLD)
				ctrl_d_exit();
		}
		if (cursor.buf[0] == '\n')
		{
			free(cursor.buf);
			cursor.buf = NULL;
			// if (history->tail->prev == history->tail->head)
			// 	history = history->tail->head;
			continue ;
		}
		add_back_cmd(&history, new_cmd_buf(ft_strdup(cursor.buf)));
		cmd = parsing_cmd(cursor.buf, env_info);
		// cmd->tail->prev->buf = ft_strdup(cursor.buf);
		hisbuf = NULL;
		if (cmd)
			exec(&cmd, &env_info);
		free(cursor.buf);
		cursor.buf = NULL;
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
// 히스토리없이 위나 아래 한번 이상 누르고 엔터치면 터짐 왜냐하면 테일의 테일이나 헤드의 헤드로 가기때문, 입력하던거 임시로 저장을 하면 공백으로 나오는경우있음 지우면될듯한데 언제지울지고민, ㅎㅣ스토리 부른다음 추가작업어려운구조