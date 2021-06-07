/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/06 18:12:51 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		main(int argc, char **argv, char **envp)
{
	t_env	*env_info;
	t_cmd	*cmd;
	char	buf[1024];
	int		end;

	(void)argv;
	if (argc > 1)
	{
		write(1, "Just execute ./minishell\n", 26);
		return (0);
	}
	env_info = parsing_env(envp);
	//signal_func();
	while (1)
	{
		prompt();
		end = read(0, buf, 1024);
		buf[end] = '\0';
		printf("0\n");
		cmd = parsing_cmd(buf, env_info);
		if (!cmd)
			continue ;
		exec(&cmd, &env_info);
	}
	return (0);
}