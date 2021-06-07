/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:03:17 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/07 15:29:20 by chanykim         ###   ########.fr       */
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
# include <termios.h>
# include <termcap.h>
# include "../libft/libft.h"

# define BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define CTRLD	4
typedef struct			s_env
{
	char				*name;
	char				*contents;
	int					equal;
	struct s_env		*next;
}						t_env;

typedef struct			s_global
{
	int					child;
	int					errcode;
}						t_global;

typedef struct			s_cursor
{
	int					c;
	int					row;
	int					col;
	char				*cm;
	char				*ce;
	char				*buf;
	int					has_buf;
}						t_cursor;


t_global				g_gv;
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
