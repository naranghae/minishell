<<<<<<< HEAD:old/src/parsing.c
#include "minishell.h"
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
>>>>>>> a772f7d4b18ac8319a235aaac37f7ccfe6c4ea18:main.c


char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
<<<<<<< HEAD:old/src/parsing.c
		free(s[i]);
		i++;
	}
	free(s);
}

// void	lst_free(t_list **lst)
// {
// 	t_list *nod;
// 	t_list *next;

// 	nod = *lst;
// 	while (nod)
// 	{
// 		next = nod->next;
// 		free(nod->obj);
// 		free(nod);
// 		nod = next;
// 	}
// }

// t_list	*lstlast(t_list *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// void		list_lst_add(t_list **lst, t_list *new, int type)
// {
// 	t_list *last;

// 	new->type = type;
// 	if (!(*lst))
// 		*lst = new;
// 	last = lstlast(*lst);
// 	last->next = new;
// 	new->next = NULL;
// }

int		is_inquote(char *buf, int start, int end)
{
	int double_q;
	int single_q;
	
	double_q = 0;
	single_q = 0;
	while (start != end)
	{
		if (buf[start] == '\'')
			single_q++;
		else if (buf[start] == '"')
			double_q++;
		start++;
	}
	if (double_q % 2 != 0 || single_q % 2 !=0 ) //둘중 하나라도 홀수면 인쿼트 = 쿼트안에있다
		return (1);
	else
		return (0);
}

// char *save_col(t_list *lst,char *buf, int offset)
// {
// 	lst_add();
// 	return (0);
// }

int ft_doublestrlen(char **s)
{
	int i;
	
	i = 0;
	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

int exec_cd(char **av)
{
	char buf[1024];
	int  ac;
	
	ac = strlen(*av);
	printf("avlen: %d\n", ac);
	printf("ac = %d, 0 : %s 1 :%s\n",ac, av[0],av[1]);
	if (ac != 2)
		return (0);
	printf("dir name: %s\n", av[1]);
	printf("before dir: %s\n", getcwd(buf, 1024));
	if(chdir(av[1]) == -1)
		printf("failed, cd\n");
	else
		printf("after dir: %s\n", getcwd(buf, 1024));
	return (0);
}


int save_col(t_list *lst,char *buf,int end)
{
	
	return (0);
}

int save_arg(char **re, int idx, char *buf, int start, int end)
{
		int i = 0;
	
	printf("arg%d, %d \n", start, end);
	if (end - start > 0)
		re[idx] = (char *)malloc(sizeof(char) * (end - start + 1));
	else
	{
		re[idx] = NULL;
		return (0);
	}
	if (!re)
		return (0);
	while (start < end)
	{
		re[idx][i] = buf[start];
		i++;
		start++;
	}
	re[idx][i] = '\0';
	return (start);
}

int save_list(char **re, int idx, char *buf, int start, int end)
{
	int i = 0;
	
	printf("list%d, %d \n", start, end);
	if (end - start > 0)
		re[idx] = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!re)
		return (0);
	while (start < end)
	{
		re[idx][i] = buf[start];
		i++;
		start++;
	}
	re[idx][i] = '\0';
	return (start);
}

int find_end(char *buf, int start, int end)
{
	while (start != end)
	{
		if (buf[start] == ' ')
			return (start);
		start++;
	}
	return (start);
}

int     find_token(char *buf)
{
	int i;
	int start;
	int re;
	
	i = 0;
	start = 0;
	re = 0;
	while (buf[i] != '\0')// ; 로 안끝나는경우도 생각
	{
		if (buf[i] == ';' || buf[i + 1] == '\0' || buf[i] == '|')
=======
		if (i >= start && j < len)
>>>>>>> a772f7d4b18ac8319a235aaac37f7ccfe6c4ea18:main.c
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
<<<<<<< HEAD:old/src/parsing.c
	return (re );
}
int		parse_token(t_list *list, char *buf,int start, int end)
=======
	str[j] = '\0';
	return (str);
}

int		main(void)
>>>>>>> a772f7d4b18ac8319a235aaac37f7ccfe6c4ea18:main.c
{
	char *str;
	char *name;
	char *contents;
	int i;
<<<<<<< HEAD:old/src/parsing.c
	int idx;
	
	re = (char **)malloc(sizeof(char *) * ((find_token(buf) ) * 2 + 1));
	printf("find_token_re: %d\n", find_token(buf));
	idx = 0;
	i = start;
	
	int end_token;
	while (i < end)
	{
		if (!is_inquote(buf, start, i))
			if (buf[i] == ' ')
			{
				i++;
				continue ;
			}
		end_token = find_end(buf, i, end);
		i = save_list(re,idx,buf, i ,end_token);//+1
		printf("%s\n", re[idx]);
		idx++;
		break ;
	}
	while (i < end && buf[i] == ' ')
			i++;
	if (i >= end)
		re[idx] = NULL;
	else
		save_arg(re, idx, buf, i , end);
	printf("%s\n", re[idx]);
	return (0);
}

int parsing_cmd(char *buf, t_list *list)
{

	t_list *lst;
	int i;
	int start;
	
	i = 0;
	start = 0;
	while (buf[i] != '\0')//; 로 안끝나는경우도 생각
=======
	str = (char *)malloc(sizeof(char) * 10);
	name = (char *)malloc(sizeof(char) * 5);
	contents = (char *)malloc(sizeof(char) * 4);
	for(int i = 0;i < 10;i++)
	{
		if (i == 5)
			str[i] = '=';
		else
			str[i] = 'a';
	}
	printf("%s\n", str);
	i = -1;
	while (str[++i] != '\0')
>>>>>>> a772f7d4b18ac8319a235aaac37f7ccfe6c4ea18:main.c
	{
		if (str[i] == '=')
		{
<<<<<<< HEAD:old/src/parsing.c
			if (!is_inquote(buf, start, i))
				if (parse_token(list, buf,start, i))
					return (0);
				start = i+1;
		}
		i++;
	}
	return (1);
=======
			name = ft_substr(str, 0, i);
			contents = ft_substr(str, i + 1, strlen(str) - (i + 1));
		}
	}
	printf("name: %s\n", name);
	printf("contents: %s\n", contents);
	return (0);
>>>>>>> a772f7d4b18ac8319a235aaac37f7ccfe6c4ea18:main.c
}