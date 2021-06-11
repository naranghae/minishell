/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:08:00 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/11 13:53:00 by hyopark          ###   ########.fr       */
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
		if ((term.c_lflag & ICANON) == ICANON)
			g_errcode = 130;
		else
			prompt();
	}
	else if (signo == SIGQUIT || signo == SIGTSTP)
	{
		if ((term.c_lflag & ICANON) == ICANON)
		{
			g_errcode = 131;
			printf("Quit: 3\n");
		}
	}
}

void	signal_func(void)
{
	tgetent(NULL, "xterm");
	signal(SIGINT, hook);
	signal(SIGQUIT, hook);
	signal(SIGTSTP, hook);
}
