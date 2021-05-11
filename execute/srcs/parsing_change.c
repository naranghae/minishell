/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:19 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/11 20:27:16 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void change_single_qute(t_cmd **list)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	int i;
	int start;
	int end;
	t_cmd *tmp;

	tmp = (*list);
	while (tmp != NULL)
	{
		i = 0;
		// printf("1\n");
		while (tmp->cmd[1][i] != '\0')
		{
			// printf("i : %d\n", i);
			// printf("12\n");
			if (/*!in_singlequote() &&*/ tmp->cmd[1][i] == '\'')
				{
					// printf("13\n");
					tmp->cmd[1][i++] = '\0';
					start = i;
					while (tmp->cmd[1][i] != '\0' && tmp->cmd[1][i] != '\'')
						i++;
					if (tmp->cmd[1][i] != '\0')
				//	printf("14\n");
					{
						end = i;
						tmp->cmd[1][end] = '\0';
						tmp->cmd[1] = ft_strjoin(tmp->cmd[1],ft_strjoin(tmp->cmd[1] + start, tmp->cmd[1] + end + 1));
						 printf("joinre : %s\n", tmp->cmd[1]);
						i = end - 1;
						continue ;
;					}
				}
			i++;
		}
		tmp = tmp->next;
	}
}
