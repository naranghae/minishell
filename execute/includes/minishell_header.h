/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:03:17 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/18 17:58:38 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HEADER_H
# define MINISHELL_HEADER_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include "../libft/libft.h"


typedef struct			s_envlist
{
	char				**envp;
	t_list				*env;
}						t_envlist;

typedef struct			s_env
{
	char				*name;
	char				*contents;
}						t_env;

void					print_env(char **env);
void					prompt(void);
t_envlist				*parsing_env(char **env);
void					signal_func(void);

#endif
