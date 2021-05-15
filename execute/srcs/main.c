/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/15 19:22:36 by hyopark          ###   ########.fr       */
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
		cmd = parsing_cmd(buf);
		exec(&cmd, &env_set, envp);
	}
	return (0);
}