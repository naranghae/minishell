/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:03:17 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/25 14:48:13 by chanykim         ###   ########.fr       */
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

# define ft_MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct			s_env
{
	char				*name;
	char				*contents;
	int					equal;
	struct	s_env		*next;
}						t_env;

void					print_env(char **env);
void					prompt(void);
t_env					*parsing_env(char **env);
t_env					*new_env(void);
void					signal_func(void);
void					save_env(t_env *env_parse, char *str, int c);
void					add_back_env(t_env **lst, t_env *new);
t_env					*new_env(void);
t_env					*last_env(t_env *lst);
#endif
