/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/07 18:42:42 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

int		main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc > 1){
		printf("Just execute ./minishell\n");
		return (0);
	}
	parsing_env(envp);
	//signal(SIGINT, 0); //interrupt program
	//signal(SIGQUIT, 0); //quit program
	//signal(SIGTSTP, 0); //stop signal generated from keyboard
	while (1)
	{
		prompt();
	}
	return (0);
}