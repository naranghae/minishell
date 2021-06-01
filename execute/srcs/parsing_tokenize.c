// #include "minishell_parsing.h"


// void	tokenize_cmd(t_cmd **tmp, int i, int idx)
// {
// 	char **word;
	
// 	word = ft_split((*tmp)->cmd[idx],' ')
// 	//아이디어1 스플릿을 살짝 수정해서 공백안에있는지없느지 확인한 후 스플릿을 떄림 스플릿 결과가 여러개이면 나머지는 아더토큰문자열에 저장시키기 실행시 그냥 cmd [1]만 남겨놓고 그거실행 후에 othertoken이 있으면 그것도 실행 -> 안됌 왜냐면 리디렉션여러개 처리가 어려워짐
// 	//아이디어 2 일단 공백만 하나로 바꿔주기

// 	while ((*tmp)->cmd[idx][i] != '\0')
// 	{
// 		while (!is_inquote((*tmp)->cmd[idx], 0, i) && (*tmp)->cmd[idx][i] != '\0'  && (*tmp)->cmd[idx][i] == ' ')
// 			i++;
// 		while (
		
		
		
		
		
		
		
// 		len = 0;
// 		type = 0;
// 		while (!is_inquote((*tmp)->cmd[idx], 0, i)&& (*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i] != '<' && (*tmp)->cmd[idx][i] != '\0')
// 			i++;
// 		if ((*tmp)->cmd[idx][i] == '<')
// 			type = IN;
// 		else if ((*tmp)->cmd[idx][i] == '>')
// 			type = OUT;
// 		if ((*tmp)->cmd[idx][i] == '\0')
// 			return ;
// 		if ((*tmp)->cmd[idx][++i] == '>' && type == OUT)
// 			type += (++i) * 0 + 1;
// 		while ((*tmp)->cmd[idx][i] == ' ' && (*tmp)->cmd[idx][i] != '\0')
// 			i++;
// 		start = i;
// 		while ((*tmp)->cmd[idx][i] != ' ' && (*tmp)->cmd[idx][i] != '\0'&& (*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i] != '<')
// 		{
// 			len++;
// 			i++;
// 		}
// 		add_back_red(&((*tmp)->red), new_red(ft_substr((*tmp)->cmd[idx], start , len), type));
// 	}

// }

// void	tokenize(t_cmd **list)
// {
// 	t_cmd *tmp;

// 	tmp = (*list)->next;
// 	while (tmp != (*list)->tail)
// 	{
// 		if (tmp->cmd[1] != NULL)
// 		{
// 			tokenize_cmd(&tmp, 0, 0);
// 			tokenize_cmd(&tmp, 0, 1);
// 		}
// 		else if  (tmp->cmd[0] != NULL)
// 			tokenize_cmd(&tmp, 0, 0);
// 		tmp = tmp->next;
// 	}
// }
