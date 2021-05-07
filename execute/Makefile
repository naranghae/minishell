# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 18:09:35 by chanykim          #+#    #+#              #
#    Updated: 2021/05/07 18:37:13 by chanykim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= main.c \
				  built_in/env.c srcs/prompt.c

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g
NAME			= minishell
AR				= ar rcs
INCDIR	= ./includes/
OBJS 			= $(SRCS:.c=.o)

%.o:	%.c
		${CC} ${CFLAGS} -I$(INCDIR) -c $< -o $@

$(NAME): 		$(OBJS)
		${CC} ${CFLAGS} -I$(INCDIR) -o $(NAME) $(OBJS)

all : $(NAME)

clean :
			$(RM) $(OBJS)

fclean : clean
			$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re