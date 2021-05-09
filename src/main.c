#include "minishell_parsing.h"

int main(int ac, char **av)
{
	char buf[1024];
	t_list  *list;
	
	while (1)
	{
		write(1,"hyochanyoung>>",14);
		int end = read(0, buf, 1024);
		buf[end] = '\0';
		list = parsing_cmd(buf);
	}
	printf("pullmergetest");
	return (0);
}