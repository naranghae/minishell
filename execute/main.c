/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 13:49:50 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_header.h"

int		main(int argc, char **argv, char **envp)
{
	t_env	*env_set;
	char	buf[1024];
	int		end;

	(void)argv;
	if (argc > 1){
		printf("Just execute ./minishell\n");
		return (0);
	}
	env_set = parsing_env(envp);
	//signal(SIGINT, hook); //interrupt program
	//signal(SIGQUIT, hook); //quit program
	//signal(SIGTSTP, hook); //stop signal generated from keyboard
	while (1)
	{
		prompt();
		end = read(0, buf, 1024);
		buf[end] = '\0';
		//cmd = readcmd();
	}
	return (0);
}