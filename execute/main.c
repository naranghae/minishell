/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 13:25:07 by chanykim         ###   ########.fr       */
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
	//signal(SIGINT, 0); //interrupt program
	//signal(SIGQUIT, 0); //quit program
	//signal(SIGTSTP, 0); //stop signal generated from keyboard
	while (1)
	{
		prompt();
		end = read(0, buf, 1024);
		buf[end] = '\0';
	}
	return (0);
}