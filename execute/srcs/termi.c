/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:18:39 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/09 21:29:23 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"


void	init_termios(void)
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

void	read_termios(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VINTR] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	signal_termios(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	term.c_cc[VINTR] = 3;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_termios(int	flag)
{
	if (flag == SET)
		init_termios();
	else if(flag == INPUT)
		read_termios();
	else if (flag == SIGON)
		signal_termios();
}
