/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/04 21:04:22 by chanykim         ###   ########.fr       */
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

// char	*remove_char(t_cursor cursor)
// {
// 	int		len;
// 	char	*ret;

// 	len = ft_strlen(cursor.buf);
// 	printf("\n remove: %s,  %d\n", cursor.buf, len);
// 	if (cursor.buf[len] == '\n')
// 		len -= 2;
// 	if (len != 0)
// 	{
// 		ret = ft_calloc(len, 1);
// 		ft_memcpy(ret, cursor.buf, len);
// 		ret[len - 1] = 0;
// 		if (cursor.buf)
// 			free(cursor.buf);
// 		return (ret);
// 	}
// 	return (cursor.buf);
// }

char	*remove_char(t_cursor cursor)
{
	int		len;
//	char	*ret;

	len = ft_strlen(cursor.buf);
	//printf("\n remove: %s,  %d  d:%d \n", cursor.buf, len, cursor.buf[len]);
	len = (len == 0) ? 1 : len;
	if (cursor.buf[len - 1] == '\n')
		cursor.buf[--len] = '\0';
	if (len != 0)
		cursor.buf[len - 1] = 0;
	return (cursor.buf);
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
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
			{
				temp = ft_atoi(&buf[i]);
				*col = 14;
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
	if ((cursor->col) <= (len + 12))
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
	cursor->col = 14;
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

	len = 0;
	if ((*cmd) == (*cmd)->head)
		return (NULL);
	if (cursor->c == UP_ARROW)
	{
		if ((*cmd)->prev == (*cmd)->tail->head)
			return ((*cmd)->buf);
		else
		{
			if ((*cmd)->buf != NULL)
				len = ft_strlen((*cmd)->buf);
			while (len--)//리스트로 과거로그를 볼 때 현재 문자열을 삭제함.
				delete_end(cursor);
			(*cmd) = (*cmd)->prev;
			write(0, (*cmd)->buf, ft_strlen((*cmd)->buf) - 1);
			cursor->col += (ft_strlen((*cmd)->buf) - 1);
			str = ft_strdup((*cmd)->buf);
			return (str);
		}
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

int		keyValue(t_cursor cursor)
{
	if (cursor.c == LEFT_ARROW || cursor.c == RIGHT_ARROW || cursor.c == BACKSPACE)
		return (0);
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_env		*env_info;
	t_cmd		*cmd;
	t_cmd		*history; //입력하고 엔터치고 저장된 문자열
	t_cursor	cursor;
	char		*hisbuf; //입력하고 있는 문자열
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
	cmd = NULL;
	hisbuf = NULL;

	while (1)
	{
		prompt();
		globalVariable();
		get_cursor_position(&cursor.col, &cursor.row);
		while (read(0, &cursor.c, sizeof(cursor.c)) > 0)
		{
		// printf("col:::%d\n",cursor.col);
			if (cursor.buf == NULL)
				cursor.buf = ft_calloc(1, sizeof(char));
			//printf("\ncol: %d\n", cursor.col);
			if (cursor.c == LEFT_ARROW)
				move_cursor_left(&cursor);
			else if (cursor.c == RIGHT_ARROW)
				move_cursor_right(&cursor);
			else if (cursor.c == BACKSPACE)
			{
				delete_end(&cursor);
				cursor.buf = remove_char(cursor);
				//printf("\ndelete: %s\n", cursor.buf);
				//cursor.buf에 담긴 거 하나씩 삭제.
			}
			else if (cursor.c == UP_ARROW ||cursor.c == DOWN_ARROW) // 위로 올리면 현재거 저장. 아래는 상관 X
			{
				len = ft_strlen(cursor.buf);
				while (len--)
					delete_end(&cursor);
				hisbuf = historyCmd(&history, &cursor);
				if (hisbuf != NULL) //history 올렸을 때 있는 문자열 저장
					cursor.buf = ft_strdup(hisbuf);
				cursor.c = 0; //flush buffer
				hisbuf = NULL;
				continue ;
			}
			else
			{
				cursor.col++;
				write(0, &cursor.c, 1);
			}
			if (hisbuf != NULL) //history 올렸을 때 있는 문자열 저장
				cursor.buf = ft_strdup(hisbuf);
			else if (keyValue(cursor))
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
			//history = history->head;
			continue ;
		}
		//printf("add: %s\n", cursor.buf);
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