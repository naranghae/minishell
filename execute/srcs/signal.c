/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:08:00 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/09 21:22:54 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	ctrl_d_exit(void)
{
	write(1, "  \b\b\n", 5);
	ft_exit(g_errcode);
}

void	hook(int signo)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	if (signo == SIGINT)
	{
		g_errcode = 1;
		write(1, "\n", 1);
		if ((term.c_lflag & ICANON) == ICANON) //프로세스 실행시 ctrl + c를 하면 종료코드 130
			g_errcode = 130;
		else
			prompt();
	}
	else if (signo == SIGQUIT || signo == SIGTSTP)
	{
		if ((term.c_lflag & ICANON) == ICANON) //프로세스 실행시 ctrl + \를 하면 종료코드 131
		{
			g_errcode = 131;
			printf("Quit: 3\n"); //종료코드 131: command not found
		}
	}
}

void	signal_func(void)
{
	tgetent(NULL, "xterm");
	signal(SIGINT, hook); //interrupt program ctrl + c
	signal(SIGQUIT, hook); //quit program ctrl + '\'
	signal(SIGTSTP, hook); //stop signal generated from keyboard ctrl + z
}