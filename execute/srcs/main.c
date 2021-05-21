/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/21 18:25:44 by chanykim         ###   ########.fr       */
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
	env_info = env_info->next;
	//signal_func();
	while (1)
	{
		prompt();
		end = read(0, buf, 1024);
		buf[end] = '\0';
		cmd = parsing_cmd(buf);
		if (!cmd)
			continue ;
		exec(&cmd, &env_info, envp);
	}
	return (0);
}