/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_inquote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:49 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 17:42:26 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int		in_singlequote(char *buf, int start, int end)
{
	int single_q;

	single_q = 0;
	while (start != end)
	{
		if (buf[start] == '\'')
			single_q++;
		start++;
	}
	if (single_q % 2 !=0) //둘중 하나라도 홀수면 인쿼트 = 쿼트안에있다
		return (1);
	else
		return (0);
}

int		in_doublequote(char *buf, int start, int end)
{
	int double_q;

	double_q = 0;
	while (start != end)
	{
		if (buf[start] == '"')
			double_q++;
		start++;
	}
	if (double_q % 2 != 0 ) //나머지가 0이면 짝수 0이아니면 홀수 홀수면 인쿼트
		return (1);
	else
		return (0);
}

int		is_inquote(char *buf, int start, int end)
{
	if (in_doublequote(buf, start, end) || in_singlequote(buf, start, end) ) //둘중 하나라도 인쿼트 = 쿼트안에있다
		return (1);
	else
		return (0);
}