/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:11 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/11 13:52:41 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int		count_parsing(char *buf, int start, int end)
{
	int idx;
	int len;
	int tmp;

	idx = 0;
	len = 0;
	while (buf[start] == ' ' && start != end)
		start++;
	tmp = start;
	while (start != end && (buf[start] == '<' || buf[start] == '>') && ++start)
		len++;
	while (start != end && (is_inquote(buf, start) || (buf[start]
		!= ' ' && buf[start] != '<' && buf[start] != '>')) && ++start)
		if ((!is_inquote(buf, tmp) && (buf[start] == ' '))
			|| (is_inquote(buf, tmp) && (buf[start] == ' '
				&& (buf[start] == '"' || buf[start] == '\''))))
			break ;
	if (start != tmp)
		len = 1;
	while (buf[start] == ' ' && start != end)
		start++;
	if (end - start > 0)
		len++;
	return (len);
}

int		init_f_v(t_first *f_v, char *buf, int start, int end)
{
	if (count_parsing(buf, start, end) == 0)
		return (0);
	f_v->idx = 0;
	f_v->len = 0;
	f_v->tmp = 0;
	f_v->re = (char **)malloc(sizeof(char *)
		* (count_parsing(buf, start, end) + 1));
	if (!f_v->re)
		return (0);
	return (1);
}

void	first_parse_stumping(char *buf, int *start, int *end, t_first *f_v)
{
	while (buf[*start] == ' ' && *start != *end)
		(*start)++;
	f_v->tmp = *start;
	while (*start != *end && (buf[*start]
		== '<' || buf[*start] == '>') && ++*start)
		f_v->len++;
	while (*start != *end && (is_inquote(buf, *start) || (buf[*start] != ' '
		&& buf[*start] != '<' && buf[*start] != '>')) && ++*start)
	{
		f_v->len++;
		if ((!is_inquote(buf, f_v->tmp) && (buf[*start] == ' '))
			|| (is_inquote(buf, f_v->tmp) && (buf[*start] == ' '
				&& (buf[*start] == '"' || buf[*start] == '\''))))
			break ;
	}
}

void	first_parse(t_cmd **list, char *buf, int start, int end)
{
	t_first	f_v;

	if (!init_f_v(&f_v, buf, start, end))
		return ;
	first_parse_stumping(buf, &start, &end, &f_v);
	start = f_v.tmp;
	f_v.re[f_v.idx++] = ft_substr(buf, f_v.tmp, f_v.len);
	start += f_v.len;
	while (buf[start] == ' ' && start != end)
		start++;
	if (end - start > 0)
		f_v.re[f_v.idx++] = ft_substr(buf, start, end - start);
	f_v.re[f_v.idx] = NULL;
	add_back_cmd(list, new_cmd(f_v.re));
	if (buf[end] == '|')
		(*list)->tail->prev->has_pip = 1;
}

t_cmd	*parsing_cmd(char *buf)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_p_c	p_v;

	init_cmd(&head, &tail, &p_v);
	if (!pre_parsing(buf))
	{
		free_cmd(&head);
		return (0);
	}
	while (buf[p_v.i] != '\0')
	{
		if ((!is_inquote(buf, p_v.i) && (buf[p_v.i] == ';'
			|| buf[p_v.i] == '|')) || buf[p_v.i + 1] == '\0')
		{
			first_parse(&head, buf, p_v.start, p_v.i++);
			p_v.start = p_v.i;
			continue ;
		}
		p_v.i++;
	}
	save_redirection(&head);
	trim_cmd(&head);
	return (head);
}
