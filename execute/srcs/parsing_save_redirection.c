#include "minishell_parsing.h"

void	save_red_cmd(t_cmd **tmp, int i, int idx)
{
	int len;
	int start;
	int type;

	while ((*tmp)->cmd[idx][i] != '\0')
	{
		len = 0;
		type = 0;
		while ((*tmp)->cmd[idx][i] != '>' && (*tmp)->cmd[idx][i] != '<')
			i++;
		if ((*tmp)->cmd[idx][i] == '<')
			type = OUT;
		else if ((*tmp)->cmd[idx][i] == '>')
			type = IN;
		if ((*tmp)->cmd[idx][++i] == '>' && type == IN)
			type += (++i);
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
}

void	save_redirection(t_cmd **list)
{
	t_cmd *tmp;

	tmp = (*list)->next;
	while (tmp != (*list)->tail)
	{
		if (tmp->cmd[1] != NULL)
			save_red_cmd(&tmp, 0, 1);
		else if  (tmp->cmd[0] != NULL)
			save_red_cmd(&tmp, 0, 0);
		tmp = tmp->next;
	}
}
