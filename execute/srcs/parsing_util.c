/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:11 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/16 16:48:50 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int		check_red(char *buf, int i, int len)
{
	while (i < len)
	{
		if (is_inquote(buf, i))
		{
			i++;
			continue ;
		}
		if (buf[i] != '\0' && (buf[i] == '>' || buf[i] == '<'))
		{
			if (buf[i + 1] != '\0' && (buf[i + 1] == '>' || buf[i + 1] == '<'))
			{
				if ((buf[i] == '>' && buf[i + 1] == '>'))
				{
					if (buf[i + 2] != '\0' && buf[i + 2] == '>')
					{
						return (0 * printf("red error\n"));
					}
				}
				else
					return (0 * printf("red error\n"));
			}
		}
		i++;
	}
	return (1);
}

char	*remove_empty_red(char *buf)
{
	char	*re;
	int		re_i;
	int		i;

	re_i = 0;
	re = buf;
	i = 0;
	while (buf[i] != '\0')
	{
		if (!is_inquote(buf, i) && buf[i] == ' ')
		{
			if (i > 0 && (buf[i - 1] == '>' || buf[i - 1] == '<'))
				while (buf[i] == ' ' && buf[i] != '\0')
					i++;
			else
				re[re_i++] = buf[i++];
			continue ;
		}
		else
			re[re_i++] = buf[i];
		i++;
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
	if (!buf || check_red(buf, 0, ft_strlen(buf) - 1) == 0)
		return (0);
	buf = remove_escape(buf, 0);
	if (!buf)
		return (0);
	buf = remove_empty(buf, 0);
	if (!buf)
		return (0);
	return (1);
}

void	trim_cmd(t_cmd **list)
{
	t_cmd	*tmp;
	char	*free_p;

	tmp = (*list)->next;
	while (tmp != (*list)->tail)
	{
		if (tmp->cmd[1] != NULL)
		{
			free_p = tmp->cmd[1];
			tmp->cmd[1] = ft_strtrim(tmp->cmd[1], " ");
			free(free_p);
		}
		tmp = tmp->next;
	}
}
