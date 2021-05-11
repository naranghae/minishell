# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 18:09:35 by chanykim          #+#    #+#              #
#    Updated: 2021/05/10 19:00:29 by chanykim         ###   ########.fr        #
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
LIBDIR	= ./libft/
LIBNAME	= libft.a
OBJS 			= $(SRCS:.c=.o)

%.o:	%.c
		${CC} ${CFLAGS} -I$(INCDIR) -c $< -o $@

$(NAME): 		$(OBJS) $(LIBNAME)
		${CC} ${CFLAGS} -I$(INCDIR) -o $(NAME) $(OBJS) $(LIBNAME)

$(LIBNAME):
			@$(MAKE) -C $(LIBDIR) bonus
			@cp $(addprefix $(LIBDIR), $(LIBNAME)) $(LIBNAME)

all : $(NAME)

clean :
			$(MAKE) clean -C $(LIBDIR)
			$(RM) $(OBJS)

fclean : clean
			@$(MAKE) fclean -C $(LIBDIR)
			$(RM) $(NAME) $(LIBNAME)

re : fclean all

.PHONY: all clean fclean re