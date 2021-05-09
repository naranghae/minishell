#include "minishell_parsing.h"

void change_single_qute(t_list **list)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	int i;
	int start;
	int end;

	while ((*list) != NULL)
	{
		i = 0;
		// printf("1\n");
		while ((*list)->cmd[1][i] != '\0')
		{
			// printf("i : %d\n", i);
			// printf("12\n");
			if (/*!in_singlequote() &&*/ (*list)->cmd[1][i] == '\'')
				{
					// printf("13\n");
					(*list)->cmd[1][i++] = '\0';
					start = i;
					while ((*list)->cmd[1][i] != '\0' && (*list)->cmd[1][i] != '\'')
						i++;
					if ((*list)->cmd[1][i] != '\0')
				//	printf("14\n");
					{
						end = i;
						(*list)->cmd[1][end] = '\0';
						(*list)->cmd[1] = ft_strjoin((*list)->cmd[1],ft_strjoin((*list)->cmd[1] + start, (*list)->cmd[1] + end + 1));
						 printf("joinre : %s\n", (*list)->cmd[1]);
						i = end - 1;
						continue ;
;					}
				}
			i++;
		}
		(*list) = (*list)->next;
	}
}
