/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:03:17 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 12:42:38 by chanykim         ###   ########.fr       */
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

typedef struct			s_env
{
	char				*name;
	char				*contents;
	struct	s_env		*next;
}						t_env;

void					env_print(char **env);
void					prompt(void);
t_env					*parsing_env(char **env);
t_env					*lstenv_new(void);

#endif
