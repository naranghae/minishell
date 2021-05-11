/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 20:55:59 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

#include "minishell_header.h"

typedef struct		s_cmd
{
	char 			**cmd;
	int				has_pip;
	int				has_red;
	struct s_cmd	*next;
}					t_cmd;

int					in_singlequote(char *buf, int start, int end);
int					in_doublequote(char *buf, int start, int end);
int					is_inquote(char *buf, int start, int end);
void				free_split(char **s);
int					mini_trim(char *buf, int start, int end);
void				first_parse(t_cmd **list, char *buf,int start,int end);
t_cmd				*save_list(t_cmd *list, char **first_parsed);
void				change_single_qute(t_cmd **list);
t_cmd				*parsing_cmd(char *buf);
t_cmd				*last_cmd(t_cmd *lst);
void				add_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd				*new_cmd(char **cmd);
void				exec_cmd(t_cmd **cmd, t_env **env_set, char **envp);
void				exec_not_built_in(t_cmd *exec_cmd, t_env *exec_env, char **envp);
#endif
