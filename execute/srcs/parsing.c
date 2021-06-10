/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:11 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 14:20:17 by hyopark          ###   ########.fr       */
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

char	*remove_empty(char *buf, int start)
{
	char	*re;
	int		re_i;

	re_i = start;
	re = buf;
	while (buf[start] != '\0')
	{
		if (!is_inquote(buf, start) && buf[start] == ' ')
		{
			re[re_i++] = ' ';
			while (buf[start] == ' ' && buf[start] != '\0')
				start++;
			continue ;
		}
		else
			re[re_i++] = buf[start];
		start++;
	}
	re[re_i] = '\0';
	return (re);
}

int		check_quote(char *buf, int i, int single_q, int double_q)
{
	while (buf[i] != '\0')
	{
		if (!single_q && buf[i] == '\\')
		{
			i += 2;
			continue ;
		}
		if (!double_q && buf[i] == '\'')
			single_q = !single_q;
		else if (!single_q && buf[i] == '"')
			double_q = !double_q;
		i++;
	}
	if (single_q == 1 || double_q == 1)
		return (0);
	else
		return (1);
}

int		check_syntax_if(char *buf, int i, int istoken)
{
	if (istoken < 1 && (buf[i] == ';' || buf[i] == '|'))
	{
		if (istoken == 2 && (buf[i - 1] == ';' || buf[i - 1] == '|'))
			return (printf("%s \'%c%c'\n", ERORR_SYN, buf[i], buf[i]) * 0);
		else if (istoken == -1 && (buf[i + 1] == ';' || buf[i + 1] == '|'))
			return (printf("%s \'%c%c'\n", ERORR_SYN, buf[i], buf[i]) * 0);
		else
			return (printf("%s \'%c'\n", ERORR_SYN, buf[i]) * 0);
	}
	else if ((buf[i] == ';' || buf[i] == '|')
		&& (buf[i + 1] == ';' || buf[i + 1] == '|'))
		return (printf("%s \'%c%c'\n", ERORR_SYN, buf[i], buf[i + 1]) * 0);
	return (1);
}

int		check_syntax(char *buf, int i, int len, int istoken)
{
	while (i < len)
	{
		if (is_inquote(buf, i))
		{
			i++;
			continue ;
		}
		if (buf[i] != ' ' && (buf[i] != ';' && buf[i] != '|' && buf[i] != '>'))
			istoken = 1;
		else if (istoken == 1 && (buf[i] == ';'
			|| buf[i] == '|' || buf[i] == '\n'))
			istoken = 2;
		else if (buf[i] != ' ')
			istoken = -1;
		if (!check_syntax_if(buf, i, istoken))
			return (0);
		i++;
	}
	return (1);
}

char	*remove_escape(char *buf, int start)
{
	char	*re;
	int		re_i;

	re_i = start;
	re = buf;
	while (buf[start] != '\0')
	{
		if (!is_inquote(buf, start) && buf[start] == '\\')
		{
			if (buf[start + 1] != '\n')
			{
				re[re_i++] = buf[start + 1];
				start += 2;
			}
			else
				return (0);
			continue ;
		}
		else
			re[re_i++] = buf[start++];
	}
	re[re_i] = '\0';
	return (re);
}

int		pre_parsing(char *buf)
{
	if (ft_strlen(buf) - 1 == 0)
		return (0);
	if (!buf || !check_quote(buf, 0, 0, 0))
		return (printf("error : match quote\n") * 0);
	if (!buf || check_syntax(buf, 0, ft_strlen(buf) - 1, 0) == 0)
		return (0);
	buf = remove_escape(buf, 0);
	if (!buf)
		return (0);
	buf = remove_empty(buf, 0);
	if (!buf)
		return (0);
	return (1);
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
