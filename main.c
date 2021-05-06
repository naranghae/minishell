#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct		s_list
{
	void			*obj;
	int				type;
	struct s_lst	*next;
}					t_list;

typedef struct		s_cmd
{
	int level;
	t_list *lst;
}					t_cmd;

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
		return (0);
	else if (s1[i] == '\0' && s2[i] != '\0')
		return (-1);
	else
		return (1);
}


static int		ft_find_c(char const *s, char c)
{
	int i;
	int re;

	i = 0;
	re = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			re++;
		}
		if (s[i])
			i++;
	}
	return (re);
}

static void		ft_put_split(char const *s, char **re, int k, int j)
{
	int		i;

	i = 0;
	while (k < j && s[k])
	{
		(*re)[i] = s[k];
		k++;
		i++;
	}
	(*re)[i] = '\0';
}

static char		**ft_freee(char **re)
{
	int		i;

	i = 0;
	while (re[i])
	{
		free(re[i]);
		i++;
	}
	free(re);
	return (0);
}

char			**ft_split(char const *s, char c)
{
	char	**re;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s || !(re = (char **)malloc(sizeof(char *) * (ft_find_c(s, c) + 1))))
		return (0);
	while (i < ft_find_c(s, c) && (size_t)k < strlen(s) && s[k])
	{
		while (s[k] == c && s[k])
			k++;
		j = k;
		while (s[j] != c && s[j])
			j++;
		if (!(re[i] = (char *)malloc(sizeof(char) * (j - k) + 1)))
			return (ft_freee(re));
		ft_put_split(s, &re[i], k, j);
		k = j;
		i++;
	}
	re[i] = 0;
	return (re);
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

	printf("%d, %d \n", start, end);

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

int save_cmd(char **re, int idx, char *buf, int start, int end)
{
	int i = 0;

	printf("cmd%d, %d \n", start, end);
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
		{
			if (!is_inquote(buf, start, i))
				{
					re++;
				}
				start = i;
		}
		i++;
	}
	return (re);
}
int		parse_token(t_cmd *cmd, char *buf,int start, int end)
{
	char	**word;
	char **re;
	int i;
	int idx;

	re = (char **)malloc(sizeof(char *) * find_token(buf) * 2);
	printf("find_token_re: %d\n", find_token(buf));
	idx = 0;
	i = start;
	// while (i != end)
	// 	if (buf[i] == ' ')
	// 		i++;
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
		i = save_cmd(re,idx,buf, i ,end_token);//+1
		printf("%s\n", re[idx]);
		idx++;
		break ;
	}

	while (i < end && buf[i] == ' ')
			i++;

	save_arg(re, idx, buf, i , end);
	printf("%s\n", re[idx]);
	//int ex;
	// while (re[ex] != NULL)
	// {
	// 	if (!ft_strncmp(re[ex],"cd",2))
			exec_cd(re);
	// 	else

	// }
	return (0);
}

int parsing_cmd(char *buf, t_cmd *cmd)
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
				if (parse_token(cmd, buf,start, i))
					return (0);
				start = i+1;
		}
		i++;
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	char buf[1024];
	t_cmd cmd;

	while (1)
	{
		write(1,"hyochanyoung$ ",14);
		int end = read(0, buf, 1024);
		buf[end] = '\0';
		write(1, buf, strlen(buf));
		parsing_cmd(buf, &cmd);
	}
	return (0);
}