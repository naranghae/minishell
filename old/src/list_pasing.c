#include "minishell.h"


int parsing_cmd(char *buf, t_list *list)
{

	t_list *lst;
	int i;
	int start;
	
	i = 0;
	start = 0;
	while (buf[i] != '\0')// ; 로 안끝나는경우도 생각
	{
		if (buf[i] == ';' || buf[i + 1] == '\0' || buf[i] == '|')
		{
			if (!is_inquote(buf, start, i))
				if (parse_token(list, buf,start, i))
					return (0);
				start = i+1;
		}
		i++;
	}
	return (1);
}