#include "minishell_parsing.h"

t_list *save_list(t_list *list, char **first_parsed)
{
	ft_lstadd_back(&list, ft_lstnew(first_parsed));
//	erro_semi(list);//짝수에 크기가 0 이면 구문오류 맨뒤에서부터 아닌거까지 세미나 파이프 오류 코드가능 빈개 하나면정상 빈개 두개면 ;오류 세개이상이면 ;;오류
	while (list!= NULL)
	{
		printf("0: %s 1: %s\n", list->cmd[0],list->cmd[1] );
		list = list->next;
	}
//	free_split(first_parsed);
	return (list);
}

void    first_parse(t_list **list, char *buf,int start,int end)
{
	char **re;
	int idx;
	int len;
	int tmp;
	
	idx = 0;
	len = 0;
	re = (char **)malloc(sizeof(char *) * 2);
	if (!re)
		return ;//(0);
	while (buf[start] == ' ' && start != end)
		start++;
	tmp = start;
	while (start != end && buf[start++] != ' ')
		len++;
	start = tmp;;
	re[idx++] = ft_substr(buf, start,len);
	start += len;
	while (buf[start] == ' ' && start != end)
		start++;
	re[idx] = ft_substr(buf, start, end - start);
	ft_lstadd_back(list, ft_lstnew(re));
	if (buf[end] == '|') // 추후에 함수로 빼서 더많은 정보들저장 가능 ex) 인자로 buf[end] 정보 넘겨서 파이프저장
		(*list)->has_pip = 1;
	
	// return (re);
}

t_list *parsing_cmd(char *buf)
{
	t_list *list;
	int i;
	int start;
	//char **first_parsed;
	
	i = 0;
	start = 0;
	list = (t_list *)malloc(sizeof(t_list));
	list = NULL;	
	while (buf[i] != '\0')// ; 로 안끝나는경우도 생각
	{
		if (buf[i] == ';' || buf[i + 1] == '\0' || buf[i] == '|')
		{
			if (!is_inquote(buf, start, i))
			{
				first_parse(&list, buf, start, i++);
				// 에러처리 -> 크기가없는거 들어올때
				// not in quote일때 공배제거 먼저해야할듯..?
				change_single_qute(&list);
				//free(first_parsed);
				start = i;
				continue ;
			}
		}
		i++;
	}
	while (list!= NULL)
	{
		printf("0: %s 1: %s 3: %d\n", list->cmd[0],list->cmd[1], list->has_pip );
		list = list->next;
	}
	return (list);
}