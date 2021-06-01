/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/01 18:23:56 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

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

void	ctrl_d_exit(void)
{
	write(1, "  \b\b\n", 5);
	ft_exit(g_gv.errcode);
}


char	*typingRead(void)
{
	char	buf[1];
	char	*out;
	int		result;
	int		ctrld;

	out = ft_calloc(1, sizeof(char));
	ctrld = 1;
	while (ctrld)
	{
		ctrld = 0;
		while ((result = read(0, buf, 1)) > 0)
		{
			out = append_char(out, *buf);
			if (*buf == '\n')
				break ;
		}
		if (!result)
		{
			if (!ft_strlen(out))
				ctrl_d_exit();
			ctrld = 1;
		}
	}
	return (out);
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

void	move_cursor_left(int *col, int *row, char *cm)
{
	if (*col == 0)
		return ;
	--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	move_cursor_right(int *col, int *row, char *cm)
{
	++(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col != 0)
		--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
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

void	globalVariable(void)
{
	g_gv.child = 0;
	g_gv.errcode = 1;
}

int		main(int argc, char **argv, char **envp)
{
	t_env	*env_info;
	t_cmd	*cmd;
	char	*buf;
	// char	*cm;
	// char	*ce;
	// struct termios term;
	// tcgetattr(STDIN_FILENO, &term);
	// term.c_lflag &= ~ICANON;
	// term.c_lflag &= ~ECHO;
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// /* init termcap */
	// tgetent(NULL, "xterm");
	// cm = tgetstr("cm", NULL); //cursor motion
	// ce = tgetstr("ce", NULL); //clear line from cursor

	firstWall(argc, argv);
	env_info = parsing_env(envp);
	signal_func();
	// int c = 0;
	// int row;
	// int col;

	// while (read(0, &c, sizeof(c)) > 0)
	// {
	// 	get_cursor_position(&col, &row);
	// 	if (c == LEFT_ARROW)
	// 		move_cursor_left(&col, &row, cm);
	// 	else if (c == RIGHT_ARROW)
	// 		move_cursor_right(&col, &row, cm);
	// 	else if (c == BACKSPACE)
	// 		delete_end(&col, &row, cm, ce);
	// 	else
	// 	{
	// 		col++;
	// 		write(0, &c, 1);
	// 	}
	// 	c = 0; //flush buffer
	// }
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
	return (0);
}