#include "minishell_parsing.h"
void	tokenize_red(t_cmd **tmp, int i, int idx)
{
	if (idx == 0 && ((*tmp)->cmd[idx][i] != '>' || (*tmp)->cmd[idx][i] != '<' ||((*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i+1] != '>')))
	{
		(*tmp)->cmd[idx] = "";
		return ;
	}
		while ((*tmp)->cmd[idx][i] != '\0')
		{
			while ((*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i] != '<' && (*tmp)->cmd[idx][i] != '\0')
				i++;
			(*tmp)->cmd[idx][i] = '\0';
			printf ("2%s2\n",(*tmp)->cmd[idx]);
			(*tmp)->cmd[idx] = ft_strtrim((*tmp)->cmd[idx]," ");
			printf ("1%s1\n",(*tmp)->cmd[idx]);
			break ;
		}
		if (ft_strlen((*tmp)->cmd[idx]) == 0)
			(*tmp)->cmd[idx] = NULL;
}

void	save_red_cmd(t_cmd **tmp, int i, int idx)
{
	int len;
	int start;
	int type;

	while ((*tmp)->cmd[idx][i] != '\0')
	{
		len = 0;
		type = 0;
		while (((*tmp)->cmd[idx][i] != '\0' && is_inquote((*tmp)->cmd[idx], i, ft_strlen((*tmp)->cmd[idx])) )|| ((*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i] != '<' && (*tmp)->cmd[idx][i] != '\0'))
			i++;
		if ((*tmp)->cmd[idx][i] == '<')
			type = IN;
		else if ((*tmp)->cmd[idx][i] == '>')
			type = OUT;
		if ((*tmp)->cmd[idx][i] == '\0')
			return ;
		if ((*tmp)->cmd[idx][++i] == '>' && type == OUT)
			type += (++i) * 0 + 1;
		while ((*tmp)->cmd[idx][i] == ' ' && (*tmp)->cmd[idx][i] != '\0')
			i++;
		start = i;
		while ((*tmp)->cmd[idx][i] != ' ' && (*tmp)->cmd[idx][i] != '\0'&& (*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i] != '<')
		{
			len++;
			i++;
		}
		add_back_red(&((*tmp)->red), new_red(ft_substr((*tmp)->cmd[idx], start , len), type));
	}
	if (type)
		tokenize_red(tmp, 0, idx);

}


void	save_redirection(t_cmd **list)//ls> filename 안돌아감 ls>filename, ls >filename 은 다됌
{
	t_cmd *tmp;

	tmp = (*list)->next;
	while (tmp != (*list)->tail)
	{
		if (tmp->cmd[1] != NULL)
		{
			save_red_cmd(&tmp, 0, 0);
			save_red_cmd(&tmp, 0, 1);
		}
		else if  (tmp->cmd[0] != NULL)
			save_red_cmd(&tmp, 0, 0);
		tmp = tmp->next;
	}
}
