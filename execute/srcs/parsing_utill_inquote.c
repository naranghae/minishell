/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_inquote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:49 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/12 17:45:56 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int		check_in_quote(char *buf, int start, int single_q, int double_q)
{
	while (buf[start] != '\0' && start < (int)ft_strlen(buf))
	{
		if (buf[start] == '\\')
		{
			start++;
			continue ;
		}
		if (!double_q && buf[start] == '\'')
		{
			if (single_q)
				single_q = 0;
			else
				single_q = 1;
		}
		else if (!single_q && buf[start] == '"')
		{
			if (double_q)
				double_q = 0;
			else
				double_q = 1;
		}
		start++;
	}
	return (!(single_q | double_q));
}

int		in_singlequote(char *buf, int end, int single_q, int double_q)
{
	int	i;

	i = 0;
	while (buf[i] != '\0' && i < end)
	{
		if ((!single_q && buf[i] == '\"' && (i > 0 &&
			buf[i - 1] != '\\')) || (i == 0 && buf[0] == '\"'))
		{
			if (double_q)
				double_q = 0;
			else
				double_q = 1;
		}
		else if ((!double_q && buf[i] == '\'' && (i > 0 &&
			buf[i - 1] != '\\')) || (i == 0 && buf[0] == '\''))
		{
			if (single_q)
				single_q = 0;
			else
				single_q = 1;
		}
		i++;
	}
	return (single_q);
}

int		in_doublequote(char *buf, int end, int single_q, int double_q)
{
	int	i;

	i = 0;
	while (buf[i] != '\0' && i < end)
	{
		if ((!single_q && buf[i] == '\"' && (i > 0 &&
			buf[i - 1] != '\\')) || (i == 0 && buf[0] == '\"'))
		{
			if (double_q)
				double_q = 0;
			else
				double_q = 1;
		}
		else if ((!double_q && buf[i] == '\'' && (i > 0 &&
			buf[i - 1] != '\\')) || (i == 0 && buf[0] == '\"'))
		{
			if (single_q)
				single_q = 0;
			else
				single_q = 1;
		}
		i++;
	}
	return (double_q);
}

int		is_inquote(char *buf, int end)
{
	if (in_doublequote(buf, end, 0, 0) || in_singlequote(buf, end, 0, 0))
		return (1);
	else
		return (0);
}
