/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/12 15:05:46 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H
# define IN 1
# define OUT 2
# define APPEND 3
# define ERORR_SYN "syntax error near unexpected token"

# include "minishell_header.h"

typedef struct			s_red
{
	int					type;
	char				*file_name;
	int					fd;
	struct s_red		*next;
}						t_red;

typedef struct			s_cmd
{
	char				*buf;
	char				**cmd;
	int					has_pip;
	t_red				*red;
	int					fd[2];
	struct s_cmd		*prev;
	struct s_cmd		*tail;
	struct s_cmd		*head;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_first
{
	char				**re;
	int					idx;
	int					len;
	int					tmp;
}						t_first;

typedef struct			s_save_red
{
	int					len;
	int					start;
	int					type;
}						t_save_red;

typedef struct			s_st_end
{
	int					st;
	int					end;
}						t_st_end;

typedef struct			s_esc
{
	char				*re;
	int					re_i;
	t_cmd				*tmp;
}						t_ecs;

typedef struct			s_c_env
{
	char				*envstr;
	int					st;
	int					i;
	int					ix;
}						t_c_env;

typedef struct			s_p_c
{
	int				i;
	int				start;
}						t_p_c;

typedef struct			s_free_p
{
	char				*tmp1;
	char				*tmp2;
	char				*tmp3;
}						t__free_p;

typedef struct			s_get_env
{
	int					i;
	int					k;
	char				*ejoin;
	char				*envjoin;
	char				**envpp;
	t_env				*env_parse;
}						t_get_env;

typedef struct			s_io
{
	int					tmp_in;
	int					tmp_out;
}						t_io;

void					exec_redirection(t_cmd *exec_cmd);
void					close_fd(t_red *red);
char					*remove_escape(char *buf, int start);
int						check_syntax(char *buf, int i, int len, int istoken);
int						check_quote(char *buf, int i,
	int single_q, int double_q);
char					*remove_empty(char *buf, int start);
int						pre_parsing(char *buf);
void					change_escape(t_cmd **cmd, int ix, int st);
void					change_env(t_cmd *tmp, t_env *env, int ix, int i);
void					change_double_qute(t_cmd *tmp,
	int ix, int i, t_st_end *st_end);
void					remove_back_cmd(t_cmd **lst);
t_cmd					*new_cmd_buf(char *buf);
void					pipe_fork(t_cmd *exec_cmd, pid_t *pid);
int						pre_exec_echo(t_cmd *exec_cmd,
	pid_t *pid);
void					close_pipe(pid_t *pid, t_cmd *exec_cmd,
	int res, int status);
int						in_singlequote(char *buf, int end, int single_q,
	int double_q);
int						in_doublequote(char *buf, int end, int single_q,
	int double_q);
int						is_inquote(char *buf, int end);
void					free_split(char **s);
int						mini_trim(char *buf, int start, int end);
void					first_parse(t_cmd **list,
	char *buf, int start, int end);
t_cmd					*save_list(t_cmd *list, char **first_parsed);
int						change_single_qute(t_cmd *tmp, int idx, int i);
void					change_qute(t_cmd **list, t_env *env, int i);
t_cmd					*parsing_cmd(char *buf);
t_red					*last_red(t_red *lst);
void					add_back_cmd(t_cmd **lst, t_cmd *new);
void					add_back_red(t_red **lst, t_red *new);
t_cmd					*new_cmd(char **cmd);
t_red					*new_red(char *file_name, int type);
void					init_cmd(t_cmd **head, t_cmd **tail, t_p_c *p_v);
void					save_redirection(t_cmd **list);
void					save_red_cmd(t_cmd **tmp, int i, int idx);
int						exec(t_cmd **cmd, t_env **env_set);
void					exec_not_built_in(t_cmd *exec_cmd, char **path,
							char **envp);
int						pre_exec_cd(t_cmd *exec_cmd, pid_t *pid);
int						pre_exec_env(t_cmd *exec_cmd, pid_t *pid,
							t_env *env_set);
int						pre_exec_export(t_cmd *exec_cmd, pid_t *pid,
							t_env *env_info);
int						pre_exec_unset(t_cmd *exec_cmd, pid_t *pid,
							t_env *env_info);
int						pre_exec_pwd(t_cmd *exec_cmd, pid_t *pid);
int						pre_exec_exit(t_cmd *exec_cmd, pid_t *pid);
int						pre_exec_exit_code(t_cmd *exec_cmd, pid_t *pid);
char					**get_envp(t_env *env_set);
void					save_red_cmd(t_cmd **tmp, int i, int idx);
void					exec_cmd(t_cmd **cmd, t_env **env_set, char **path);
void					free_cmd(t_cmd **cmd);
int						check_in_quote(char *buf, int start, int single_q,
							int double_q);
int						listlen(t_env *env_info);
int						listlen_all(t_env *env_info);
int						env_add(char *cmd, t_env *env_info);
int						equal_is(char *cmd);
void					store_contents(char **contents, t_env *env_parse,
							t_env *exec_env);
int						name_search(t_env *env_parse, t_env *env_info);
void					env_sort_print(t_env *env_info);
int						except_check(char *exportcmd, int type);
int						cmd_error(char *cmd, int error);
int						exec_pwd(void);
int						ft_exit(int exitcode);
void					int_exec_exit(t_cmd *exec_cmd, pid_t *pid);
void					trim_cmd(t_cmd **list);
void					pre_exec_cmd(t_cmd **cmd, t_env **env_set,
							char **path);
void					exec_intro(t_cursor *cursor, t_cmd *cmd,\
							t_env *env_info);
void					env_clean(t_env *env_info);
void					swaplist(t_env *env, t_env *env_next);
#endif
