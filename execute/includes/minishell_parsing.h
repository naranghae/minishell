/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/24 14:27:58 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H
# define IN 1
# define OUT 2
# define APPEND 3

#include "minishell_header.h"


typedef struct		s_red
{
	int				type;
	char			*file_name;
	int			fd;
	struct s_red	*next;
}					t_red;

typedef struct		s_cmd
{
	char 			**cmd;
	int				has_pip;
	t_red			*red;
	int				fd[2];
	struct s_cmd	*prev;
	struct s_cmd	*next;
	struct s_cmd	*tail;
}					t_cmd;

void	pipe_fork(t_cmd *exec_cmd,pid_t *pid);
void pre_exec_cd(t_cmd *exec_cmd, pid_t pid);
void pre_exec_echo(t_cmd *exec_cmd, pid_t *pid);
void pre_exec_env(t_cmd *exec_cmd, pid_t *pid, t_env **env_set);
void	close_pipe(pid_t *pid, t_cmd *exec_cmd, int res, int status);



int					in_singlequote(char *buf, int start, int end);
int					in_doublequote(char *buf, int start, int end);
int					is_inquote(char *buf, int start, int end);
void				free_split(char **s);
int					mini_trim(char *buf, int start, int end);
void				first_parse(t_cmd **list, char *buf,int start,int end);
t_cmd				*save_list(t_cmd *list, char **first_parsed);
void				change_single_qute(t_cmd **list);
t_cmd				*parsing_cmd(char *buf);
t_red				*last_red(t_red *lst);
void				add_back_cmd(t_cmd **lst, t_cmd *new);
void				add_back_red(t_red **lst, t_red *new);
t_cmd				*new_cmd(char **cmd);
t_red				*new_red(char *file_name, int type);
void				init_cmd(t_cmd **head, t_cmd **tail);
void				save_redirection(t_cmd **list);
void				save_red_cmd(t_cmd **tmp, int i, int idx);
void				exec_cmd(t_cmd **cmd, t_env **env_set, char **envp, char **path);
int					exec(t_cmd **cmd, t_env **env_set, char **envp);
void				exec_not_built_in(t_cmd *exec_cmd, char **path, char **envp);
void	free_cmd(t_cmd **cmd);
int		check_in_quote(char *buf, int start, int end);

#endif
