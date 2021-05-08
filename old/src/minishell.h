#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct		s_contents
{
	int has_pipe;
	int has_redirect;
	char **cmd;
}					t_contents;

typedef struct		s_list
{
	int has_pipe;//구조체로
	int has_redirect;//구조체로
	//int has_;
	char **cmd;
	struct s_lst	*next;
}					t_list;


int					ft_strncmp(const char *s1, const char *s2, size_t n);
static int		ft_find_c(char const *s, char c);
static void		ft_put_split(char const *s, char **re, int k, int j);
static char		**ft_freee(char **re);
char			**ft_split(char const *s, char c);
void	free_split(char **s);
int		is_inquote(char *buf, int start, int end);
int ft_doublestrlen(char **s);
int exec_cd(char **av);
int save_col(t_list *lst,char *buf,int end);
int save_arg(char **re, int idx, char *buf, int start, int end);
int save_cmd(char **re, int idx, char *buf, int start, int end);
int find_end(char *buf, int start, int end);
int		parse_token(t_list *cmd, char *buf,int start, int end);
int parsing_cmd(char *buf, t_list *cmd);

#endif