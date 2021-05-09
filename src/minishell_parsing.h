#ifndef MINISHELL_PARSING_H
#define MINISHELL_PARSING_H

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

t_list	*ft_lstnew(char **cmd);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		in_singlequote(char *buf, int start, int end);
int		in_doublequote(char *buf, int start, int end);
int		is_inquote(char *buf, int start, int end);
void	free_split(char **s);
size_t		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int mini_trim(char *buf, int start, int end);
void    first_parse(t_list **list, char *buf,int start,int end);
t_list *save_list(t_list *list, char **first_parsed);
void change_single_qute(t_list **list);
t_list *parsing_cmd(char *buf);

#endif