/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:03:17 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/09 21:12:02 by chanykim         ###   ########.fr       */
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
# define CTRLC	3
# define CTRLD	4
# define SET	0
# define INPUT	1
# define SIGON	2

typedef struct				s_env
{
	char					*name;
	char					*contents;
	char					**envp;
	int						equal;
	struct s_env			*next;
}							t_env;

typedef struct				s_cursor
{
	int						c;
	int						row;
	int						col;
	char					*cm;
	char					*ce;
	char					*buf;
	int						listcircle;
}							t_cursor;

typedef struct				s_history
{
	char					*buf;
	struct s_history		*prev;
	struct s_history		*tail;
	struct s_history		*head;
	struct s_history		*next;
}							t_history;

int							g_errcode;
void						print_env(char **env);
void						prompt(void);
t_env						*parsing_env(char **env);
t_env						*new_env(void);
void						signal_func(void);
void						save_env(t_env *env_parse, char *str, int c);
void						add_back_env(t_env **lst, t_env *new);
t_env						*new_env(void);
t_env						*last_env(t_env *lst);
void						init_termios(void);
void						read_termios(void);
void						signal_termios(void);
void						set_termios(int	flag);
void						print_buf(t_cursor *cursor, char *buf);
void						ctrl_d_exit(void);
int							historylst_num(t_history *history);
int							nbr_length(int n);
void						get_cursor_position(int *col, int *rows);
int							putchar_tc(int tc);
void						move_cursor_left(t_cursor *cursor);
void						move_cursor_right(t_cursor *cursor);
void						delete_end(t_cursor *cursor);
void						init_cursor(t_cursor *cursor);
char						*history_up(t_history **cmd, t_cursor *cursor);
char						*history_down(t_history **cmd, t_cursor *cursor);
t_history					*init_history(void);
void						history_ht(t_history **head, t_history **tail);
void						add_back_his(t_history **lst, t_history *new);
t_history					*new_his_buf(char *buf);
t_history					*new_his(void);
char						*append_char(t_cursor cursor);
char						*remove_char(t_cursor cursor);
void						firstWall(int argc, char **argv);
void						print_buf(t_cursor *cursor, char *buf);
int							keyValue(t_cursor cursor);
#endif
