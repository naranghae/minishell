# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 18:09:35 by chanykim          #+#    #+#              #
#    Updated: 2021/05/26 12:27:30 by chanykim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc -g3 -fsanitize=address

CFLAGS			= -Wall -Wextra -Werror

LIBFTD = ./includes/libft

LIBFT = libft.a

SRCD = ./srcs/

SRC=	main.c\
		env.c\
		prompt.c\
		signal.c\
		parsing_change.c\
		parsing_utill_free.c\
		parsing_utill_inquote.c\
		parsing_utill_list.c\
		parsing_utill_str.c\
		parsing_save_redirection.c\
		parsing.c\
		exec.c\
		exec_cd.c\
		exec_echo.c\
		exec_export.c\
		exec_env.c\
		exec_not_built_in.c\
		exec_util.c \
		export_add.c \
		export_swap.c \
		export_except.c

SRCM = $(addprefix $(SRCD), $(SRC))

INCLUDE = -I $(LIBFTD) -I ./includes

all : $(NAME)

clean :
		$(MAKE) -C $(LIBFTD) clean

fclean : clean
		$(MAKE) -C $(LIBFTD) fclean
		rm -rf $(NAME)

re : fclean all

$(NAME) : $(LIBFTD)/$(LIBFT)
		$(CC) $(CFLAGS) -L $(LIBFTD) -lft $(INCLUDE) -o $@ $(SRCM)

$(LIBFTD)/$(LIBFT) :
	$(MAKE) -C $(LIBFTD) all

.PHONY : all clean fclean re
