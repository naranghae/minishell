/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:11 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/15 20:05:06 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

t_cmd *save_list(t_cmd *list, char **first_parsed)
{
	add_back_cmd(&list, new_cmd(first_parsed));
//	erro_semi(list);//짝수에 크기가 0 이면 구문오류 맨뒤에서부터 아닌거까지 세미나 파이프 오류 코드가능 빈개 하나면정상 빈개 두개면 ;오류 세개이상이면 ;;오류
	while (list!= NULL)
	{
		printf("0: %s 1: %s\n", list->cmd[0],list->cmd[1] );
		list = list->next;
	}
//	free_split(first_parsed);
	return (list);
}

int     count_parsing(char *buf,int start,int end)
{
	int re;
	int idx;
	int len;
	int tmp;

	re = 0;
	idx = 0;
	len = 0;

	while (buf[start] == ' ' && start != end)
		start++;
	tmp = start;
	while (start != end && buf[start++] != ' ')
		len++;
	start = tmp;
	re++;
	start += len;
	while (buf[start] == ' ' && start != end)
		start++;
	if (end - start > 0)
		re++;
	return (re);
}


void    first_parse(t_cmd **list, char *buf,int start,int end)
{
	char **re;
	int idx;
	int len;
	int tmp;

	idx = 0;
	len = 0;
//	printf ("mal: %d\n",count_parsing(buf, start, end));
	re = (char **)malloc(sizeof(char *) * (count_parsing(buf, start, end) + 1));
	if (!re)
		return ;//(0);
	while (buf[start] == ' ' && start != end)
		start++;
	tmp = start;
	while (start != end && buf[start++] != ' ')
		len++;
	start = tmp;
	re[idx++] = ft_substr(buf, start,len);
	start += len;
	while (buf[start] == ' ' && start != end)
		start++;
	if (end - start > 0)
	{
		re[idx++] = ft_substr(buf, start, end - start);
		re[idx] = NULL;
	}
	else
		re[idx] = NULL;
	add_back_cmd(list, new_cmd(re));
	if (buf[end] == '|') // 추후에 함수로 빼서 더많은 정보들저장 가능 ex) 인자로 buf[end] 정보 넘겨서 파이프저장
		(*list)->tail->prev->has_pip = 1;
	// return (re);
}

t_cmd *parsing_cmd(char *buf)
{
	t_cmd *head;
	t_cmd *tail;
	int i;
	int start;
	//char **first_parsed;
	i = 0;
	start = 0;
	init_cmd(&head, &tail);
	while (buf[i] != '\0')// ; 로 안끝나는경우도 생각
	{
		if (buf[i] == ';' || buf[i + 1] == '\0' || buf[i] == '|')
		{
			if (!is_inquote(buf, start, i))
			{
				first_parse(&head, buf, start, i++);
				// 에러처리 -> 크기가없는거 들어올때
				// not in quote일때 공배제거 먼저해야할듯..?
				//free(first_parsed);
				start = i;
				continue ;
			}
		}
		i++;
	}
				change_single_qute(&head);
	//first_parse(&head, buf, start, ft_strlen(buf));
	// printf("%s %s\n", head->cmd[0], head->cmd[1]);
	// while (head!= NULL)
	// {
	// 	printf("0: %s 1: %s 3: %d\n", head->cmd[0],head->cmd[1], head->has_pip);
	// 	head = head->next;
	// }
	return (head);
}