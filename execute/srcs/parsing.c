/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:33:11 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/24 20:40:23 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

// t_cmd	*save_list(t_cmd *list, char **first_parsed)
// {
// 	add_back_cmd(&list, new_cmd(first_parsed));
// //	erro_semi(list);//짝수에 크기가 0 이면 구문오류 맨뒤에서부터 아닌거까지 세미나 파이프 오류 코드가능 빈개 하나면정상 빈개 두개면 ;오류 세개이상이면 ;;오류
// 	while (list!= NULL)
// 	{
// 		printf("0: %s 1: %s\n", list->cmd[0],list->cmd[1] );
// 		list = list->next;
// 	}
// //	free_split(first_parsed);
// 	return (list);
// }

int		count_parsing(char *buf,int start,int end)
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
	while (start != end && (buf[start] == '<' || buf[start] == '>') && ++start)//명령어 크기 재기
		len++;
while (start != end && (is_inquote(buf,start,end) || (buf[start] != ' ' && buf[start] != '<' && buf[start] != '>')) &&  ++start)//명령어 크기 재기
	{
		if (is_inquote(buf, tmp, start) && (buf[start] == ' ' || buf[start] == '"'))
			break ;
		len++;
	}
	//start = tmp;
	if (start != tmp)
		re++;
	//start += len;
	while (buf[start] == ' ' && start != end)
		start++;
	if (end - start > 0)
		re++;
	return (re);
}

void	 first_parse(t_cmd **list, char *buf,int start,int end)
{
	char **re;
	int idx;
	int len;
	int tmp;

	idx = 0;
	len = 0;
	printf ("cp : %d\n", count_parsing(buf, start, end));
	if (count_parsing(buf, start, end) == 0)
		return ;
	re = (char **)malloc(sizeof(char *) * (count_parsing(buf, start, end) + 1));
	if (!re)
		return ;//(0);
	while (buf[start] == ' ' && start != end)//앞공백제거
		start++;
	tmp = start;
	while (start != end && (buf[start] == '<' || buf[start] == '>') && ++start)//명령어 크기 재기
		len++;
	while (start != end && (is_inquote(buf,start,end) || (buf[start] != ' ' && buf[start] != '<' && buf[start] != '>')) &&  ++start)//명령어 크기 재기
	{
		if (is_inquote(buf, tmp, start) && (buf[start] == ' ' || buf[start] == '"'))
			break ;
		len++;
	}
		 printf ("start : %d ,end : %d len : %d\n", tmp,end,len);
	start = tmp;
	re[idx++] = ft_substr(buf, tmp, len);//명령어저장
	start += len;
	while (buf[start] == ' ' && start != end)//
		start++;
				// printf ("start : %d ,end : %d len : %d\n", start,end,len);

	if (end - start > 0)
	// {
		re[idx++] = ft_substr(buf, start, end - start);
	// 	re[idx] = NULL;
	// }
	//else
		re[idx] = NULL;
	add_back_cmd(list, new_cmd(re));
	// if (end - start > 0)
	// 	free(re[idx--]);
	// else
	// 	free(re[idx]);
	int j = 0;
		printf("firstpasing\n");
	while (re[j] != NULL)
	{
	printf("re: %s\n",re[j]);
	j++;
	}
	if (buf[end] == '|') // 추후에 함수로 빼서 더많은 정보들저장 가능 ex) 인자로 buf[end] 정보 넘겨서 파이프저장
		(*list)->tail->prev->has_pip = 1;
	}

char	*remove_empty(char *buf, int start, int end)
{
	char *re;
	int re_i;
	
	re_i = start;
	re = buf;
	while (buf[start] != '\0')
	{
		if (!is_inquote(buf, start, end) &&buf[start] == ' ')
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

int		check_quote(char *buf, int len)
{
	int i;
	int single_q;
	int double_q;

	i = 0;
	single_q = 0;//1 열림 0 닫힘
	double_q = 0;
	len = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\'')
		{
			i++;
			single_q = 1;
			while (buf[i] != '\0' && buf[i] != '\'')
				i++;
			if (buf[i] == '\'')
			{
				single_q = 0;
				i++;
			}
			// printf (" i : %d c : %c \n",i, buf[i]);
			continue ;
		}
		else if (buf[i] == '"')
		{
			i++;
			double_q = 1;
			while (buf[i] != '\0' && buf[i++] != '"')
				i++;
			if (buf[i] == '"')
			{
				double_q = 0;
				i++;
			}
			continue ;
		}
		i++;
	}
	// printf ("sing : %d doub : %d\n",single_q,double_q);
	if (single_q == 1|| double_q == 1)// match가 안된경우
		return (0);
	else
		return (1);
}

int check_syntax(char *buf, int i, int len, int istoken)
{	
	if (len == 0)
		return (0);
	if (!check_quote(buf, len))
		return (printf("error : match quote\n") * 0);
	while (i < len)
	{
		if (buf[i] != ' ' && (buf[i] != ';' && buf[i] != '|' && buf[i] != '>'))
			istoken = 1;
		else if (istoken == 1 && (buf[i] == ';' || buf[i] == '|' ||  buf[i] == '\n'))
			istoken = 2;
		else if (buf[i] != ' ' )
			istoken = -1;
		if (istoken < 1 && (buf[i] == ';' || buf[i] == '|'))
		{
			if (istoken == 2 && (buf[i - 1] == ';' || buf[i - 1] == '|'))
				return(printf("syntax error near unexpected token \'%c%c'\n", buf[i], buf[i]) * 0);
			else if (istoken == -1 && (buf[i + 1] == ';' || buf[i + 1] == '|'))
				return(printf("syntax error near unexpected token \'%c%c'\n", buf[i], buf[i]) * 0);
			else
				return(printf("syntax error near unexpected token \'%c'\n", buf[i]) * 0);
		}
		i++;
	}
	return (1);
}

t_cmd *parsing_cmd(char *buf, t_env *env)
{
	t_cmd *head;
	t_cmd *tail;
	int i;
	int start;

	i = 0;
	start = 0;
	init_cmd(&head, &tail);
	buf = remove_empty(buf, 0, ft_strlen (buf));
	if (check_syntax(buf, 0, ft_strlen(buf) - 1, 0) == 0)
		return (0);
	while (buf[i] != '\0')// ; 로 안끝나는경우도 생각
	{
		if (check_in_quote(buf, start, i) && (buf[i] == ';' || buf[i + 1] == '\0' || buf[i] == '|'))
		{
				 first_parse(&head, buf, start, i++);
				// 에러처리 -> 크기가없는거 들어올때
				// not in quote일때 공배제거 먼저해야할듯..?
				//free(first_parsed);
				start = i;
				continue ;
		}
		i++;
	}
	save_redirection(&head);
	change_qute(&head, env, 1);
	return (head);
}