/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/24 14:04:58 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		main(int argc, char **argv, char **envp)
{
	t_env	*env_set;
	t_cmd	*cmd;
	char	buf[1024];
	int		end;

	(void)argv;
	if (argc > 1)
	{
		write(1, "Just execute ./minishell\n", 26);
		return (0);
	}
	env_set = parsing_env(envp);
	env_set = env_set->next;
	//signal_func();
	while (1)
	{
		prompt();
		end = read(0, buf, 1024);
		buf[end] = '\0';
		printf("0\n");
		cmd = parsing_cmd(buf);
		printf("1\n");
		if (cmd == 0)
			continue ;
		exec(&cmd, &env_set, envp);
	//	free_cmd(&cmd);
	}
	return (0);
}