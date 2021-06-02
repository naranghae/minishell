/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:08:00 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/02 16:46:24 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	hook(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		g_gv.errcode = 1;
		if (g_gv.child) //프로세스 실행시 ctrl + c를 하면 종료코드 130
			g_gv.errcode = 130;
		else
			prompt();
	}
	else if (signo == SIGQUIT || signo == SIGTSTP)
	{
		g_gv.errcode = 131;
		if (g_gv.child) //프로세스 실행시 ctrl + \를 하면 종료코드 131
			printf("^\\Quit: 3\n"); //종료코드 131: command not found
	}
}

void	signal_func(void)
{
	signal(SIGINT, hook); //interrupt program ctrl + c
	signal(SIGQUIT, hook); //quit program ctrl + '\'
	signal(SIGTSTP, hook); //stop signal generated from keyboard ctrl + z
}