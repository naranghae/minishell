/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util_pre.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:11 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/15 16:44:54 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

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
	re = remove_empty_red(re);
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
