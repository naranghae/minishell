#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#ifndef MINISHELL_HEADER_H
# define MINISHELL_HEADER_H

typedef struct	s_env
{
	char		*name;
	char		*contents;
	t_env		*next;
}				t_env;


void			env_print(char **env);
void			prompt(void);

#endif