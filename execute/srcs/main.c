/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/15 16:39:26 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		main(int argc, char **argv, char **envp)
{
	t_env		*env_info;
	t_cmd		*cmd;
	t_history	*history;
	t_cursor	cursor;

	firstwall(argc, argv);
	env_info = parsing_env(envp);
	history = init_history();
	signal_func();
	cmd = NULL;
	while (1)
	{
		prompt();
		set_termios(SET);
		init_cursor(&cursor);
		input_mode(&cursor, &history);
		exec_intro(&cursor, cmd, env_info);
	}
	return (0);
}
