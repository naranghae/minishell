/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/02 17:07:37 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"


// char	*append_char(char *org, char c)
// {
// 	const int len = ft_strlen(org);
// 	char *const	ret = ft_calloc(len + 2, 1);

// 	ft_memcpy(ret, org, len);
// 	ret[len] = c;
// 	ret[len + 1] = 0;
// 	if (org)
// 		free(org);
// 	return (ret);
// }

void	ctrl_d_exit(void)
{
	write(1, "  \b\b\n", 5);
	ft_exit(g_gv.errcode);
}

// char	*typingRead(void)
// {
// 	char	buf[1];
// 	char	*out;
// 	int		result;
// 	int		ctrld;

// 	out = ft_calloc(1, sizeof(char));
// 	ctrld = 1;
// 	while (ctrld)
// 	{
// 		ctrld = 0;
// 		while ((result = read(0, buf, 1)) > 0)
// 		{
// 			out = append_char(out, *buf);
// 			if (*buf == '\n')
// 				break ;
// 		}
// 		if (!result)
// 		{
// 			if (!ft_strlen(out))
// 				ctrl_d_exit();
// 			ctrld = 1;
// 		}
// 	}
// 	return (out);
// }

char	*append_char(char *org, char c)
{
	const int len = ft_strlen(org);
	char *const	ret = ft_calloc(len + 2, 1);

	ft_memcpy(ret, org, len);
	ret[len] = c;
	ret[len + 1] = 0;
	if (org)
		free(org);
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
	if (cursor->col != 0)
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

	cursor->cm = tgetstr("cm", NULL); //cursor motion
	cursor->ce = tgetstr("ce", NULL); //clear line from cursor
	cursor->c = 0;
}

void	globalVariable(void)
{
	g_gv.child = 0;
	g_gv.errcode = 1;
}

int		main(int argc, char **argv, char **envp)
{
	t_env		*env_info;
	t_cmd		*cmd;
	char		*buf;
	t_cursor	cursor;

	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	/* init termcap */
	tgetent(NULL, "xterm");
	initCursor(&cursor);

	firstWall(argc, argv);
	env_info = parsing_env(envp);
	signal_func();
	buf = NULL;

	while (1)
	{
		prompt();
		globalVariable();
		while (read(0, &cursor.c, sizeof(cursor.c)) > 0)
		{
			if (buf == NULL)
				buf = ft_calloc(1, sizeof(char));
			//printf("\nretbuf: %s\n", buf);
			get_cursor_position(&cursor.col, &cursor.row);
			//buf = typingRead();
			if (cursor.c == LEFT_ARROW)
				move_cursor_left(&cursor);
			else if (cursor.c == RIGHT_ARROW)
				move_cursor_right(&cursor);
			else if (cursor.c == BACKSPACE)
				delete_end(&cursor);
			else
			{
				cursor.col++;
				write(0, &cursor.c, 1);
			}
			buf = append_char(buf, cursor.c);
			if (cursor.c == '\n')
			{
				cursor.c = 0; //flush buffer
				break ;
			}
			cursor.c = 0; //flush buffer
			//printf("%s, %d\n", buf, (int)buf);
			if (buf[0] == CTRLD)
				ctrl_d_exit();
		}
		if (buf[0] == '\n')
		{
			free(buf);
			buf = NULL;
			continue ;
		}
		cmd = parsing_cmd(buf, env_info);
		if (cmd)
			exec(&cmd, &env_info);
		free(buf);
		buf = NULL;
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