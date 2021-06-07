/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_inquote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:49 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/07 15:34:53 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"


// int		check_in_quote(char *buf, int start, int end)
// {
// 	int single_q;
// 	int double_q;

// 	single_q = 0;//1 열림 0 닫힘
// 	double_q = 0;
// 	while (start < end)
// 	{
// 		if (buf[start] == '\'')
// 		{
// 			start++;
// 			single_q = 1;
// 			while (buf[start] != '\0' && buf[start] != '\'')
// 				start++;
// 			if (buf[start] == '\'')
// 			{
// 				single_q = 0;
// 				start++;
// 			}
// 			// printf (" i : %d c : %c \n",i, buf[start]);
// 			continue ;
// 		}
// 		else if (buf[start] == '"')
// 		{
// 			double_q = 1;
// 			while (buf[start] != '\0' && buf[start++] != '"')
// 			start++;
// 			if (buf[start] == '"')
// 				double_q = 0;
// 			continue ;
// 		}
// 		start++;
// 	}
// 	if (single_q == 1|| double_q == 1)// match가 안된경우
// 		return (0);
// 	else
// 		return (1);
// }

int		check_in_quote(char *buf, int start, int end)
{
	int i;
	int single_q;
	int double_q;

	i = start;
	single_q = 0;//1 열림 0 닫힘
	double_q = 0;
	while (buf[i] != '\0' && start < end)
	{
		if (buf[i] == '\\')
		{
			i++;
			continue ;
		}
		if (!double_q && buf[i] == '\'')
		{
			if (single_q)
				single_q = 0;
			else
				single_q = 1;
		}
		else if (!single_q && buf[i] == '"')
		{
			if (double_q)
				double_q = 0;
			else
				double_q = 1;
		}
		i++;
	}
	// printf ("sing : %d doub : %d\n",single_q,double_q);
	if (single_q == 1|| double_q == 1)// match가 안된경우
		return (0);
	else
		return (1);
}

// int		in_singlequote(char *buf, int start, int end)
// {
// 	int single_q;

// 	single_q = 0;
// 	while (start != end)
// 	{
// 		if (buf[start] == '\'')
// 			single_q++;
// 		start++;
// 	}
// 	if (single_q % 2 !=0) //둘중 하나라도 홀수면 인쿼트 = 쿼트안에있다
// 		return (1);
// 	else
// 		return (0);
// }

// int		in_doublequote(char *buf, int start, int end)
// {
// 	int double_q;

// 	double_q = 0;
// 	while (start != end)
// 	{
// 		if (buf[start] == '"')
// 			double_q++;
// 		start++;
// 	}
// 	if (double_q % 2 != 0 ) //나머지가 0이면 짝수 0이아니면 홀수 홀수면 인쿼트
// 		return (1);
// 	else
// 		return (0);
// }

// int		check_in_quote(char *buf, int start, int end)
// {
// 	int i;
// 	int single_q;
// 	int double_q;

// 	i = start;
// 	single_q = 0;//1 열림 0 닫힘
// 	double_q = 0;
// 	while (buf[i] != '\0' && start < end)
// 	{
// 		if (buf[i] == '\\')
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (!double_q && buf[i] == '\'')
// 		{
// 			if (single_q)
// 				single_q = 0;
// 			else
// 				single_q = 1;
// 		}
// 		else if (!single_q && buf[i] == '"')
// 		{
// 			if (double_q)
// 				double_q = 0;
// 			else
// 				double_q = 1;
// 		}
// 		i++;
// 	}
// 	// printf ("sing : %d doub : %d\n",single_q,double_q);
// 	if (single_q == 1|| double_q == 1)// match가 안된경우
// 		return (0);
// 	else
// 		return (1);
// }

int		in_singlequote(char *buf, int start, int end)
{
	int single_q;
	int double_q;

	single_q = 0;
	double_q = 0;
	end = start;
	start = 0;
	while (buf[start] != '\0' && start < end)
	{
		if (!single_q && buf[start] == '\"')
		{
			if(double_q)
				double_q = 0;
			else
				double_q = 1;
		}
		else if (!double_q && buf[start] == '\'')
		{
			if(single_q)
				single_q = 0;
			else
				single_q = 1;
		}
		start++;
	}
	if (single_q == 1) //둘중 하나라도 홀수면 인쿼트 = 쿼트안에있다
		return (1);
	else
		return (0);
}

int		in_doublequote(char *buf, int start, int end)
{
	int single_q;
	int double_q;

	single_q = 0;
	double_q = 0;
	end = start;
	start = 0;


	while (buf[start] != '\0' && start < end)
	{
		if (!single_q && buf[start] == '\"')
		{
			if(double_q)
				double_q = 0;
			else
				double_q = 1;
		}
		else if (!double_q && buf[start] == '\'')
		{
			if(single_q)
				single_q = 0;
			else
				single_q = 1;
		}
		start++;
	}
	if (double_q == 1) //둘중 하나라도 홀수면 인쿼트 = 쿼트안에있다
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