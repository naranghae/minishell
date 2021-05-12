/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:08:00 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 18:01:37 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	hook(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\b\b  \n", 5);
		prompt();
	}
	else if (signo == SIGQUIT)
		exit(1);
}

void	signal_func(void)
{
	signal(SIGINT, hook); //interrupt program ctrl + c
	signal(SIGQUIT, hook); //quit program ctrl + '\'
}