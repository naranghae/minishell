
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct		s_list
{
	char 			**cmd;
	int				has_pip;
	int				has_red;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(char **cmd)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->cmd = cmd;
	new->has_pip = 0;
	new->has_red = 0;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (!*lst)
		*lst = new;
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->next = NULL;
}

int		in_singlequote(char *buf, int start, int end)
{
	int single_q;
	
	single_q = 0;
	while (start != end)
	{
		if (buf[start] == '\'')
			single_q++;
		start++;
	}
	if (single_q % 2 !=0) //둘중 하나라도 홀수면 인쿼트 = 쿼트안에있다
		return (1);
	else
		return (0);
}

int		in_doublequote(char *buf, int start, int end)
{
	int double_q;
	
	double_q = 0;
	while (start != end)
	{
		if (buf[start] == '"')
			double_q++;
		start++;
	}
	if (double_q % 2 != 0 ) //나머지가 0이면 짝수 0이아니면 홀수 홀수면 인쿼트
		return (1);
	else
		return (0);
}

int		is_inquote(char *buf, int start, int end)
{
	if (in_doublequote(buf, start, end) || in_singlequote(buf, start, end) ) //둘중 하나라도 인쿼트 = 쿼트안에있다
		return (1);
	else
		return (0);
}

void	free_split(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

size_t		ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*re;
	size_t	i;

	i = 0;
	re = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!re)
		return (0);
	while (s1[i] != '\0')
	{
		re[i] = s1[i];
		i++;
	}
	re[i] = '\0';
	return (re);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*re;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	re = (char *)malloc(sizeof(char) * len + 1);
	if (!re)
		return (0);
	if (start >= ft_strlen(s))
		return (0);
	while (i < len)
		re[i++] = s[start++];
	re[i] = '\0';
	return (re);
}

int mini_trim(char *buf, int start, int end)
{	
	while (buf[start] == ' ' && start != end)
		start++;
	return (start);
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

// erro_semi(t_list *list)
// {

// 	while ()
// }



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

void change_single_qute(t_list **list)
{
	
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