# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 18:09:35 by chanykim          #+#    #+#              #
#    Updated: 2021/06/15 14:16:05 by chanykim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc #-g3 -fsanitize=address

CFLAGS			= -Wall -Wextra -Werror -lncurses -ltermcap

LIBFTD = ./includes/libft

LIBFT = libft.a

SRCD = ./srcs/

SRC=	main.c\
		main_util.c \
		env.c\
		prompt.c\
		signal.c\
		parsing_change.c\
		parsing_change_env.c\
		parsing_change_double.c\
		parsing_change_single.c\
		parsing_change_esc.c\
		parsing_utill_free.c\
		parsing_utill_inquote.c\
		parsing_utill_list_cmd.c\
		parsing_utill_list_red.c\
		parsing_utill_str.c\
		parsing_save_redirection.c\
		parsing_util_pre.c\
		parsing_util.c\
		parsing.c\
		exec.c\
		exec_red.c\
		exec_cd.c\
		exec_echo.c\
		exec_export.c\
		exec_env.c\
		exec_not_built_in.c\
		exec_util.c \
		exec_exit_code.c\
		export_add.c \
		export_swap.c \
		export_except.c \
		exec_unset.c \
		exec_pwd.c \
		exec_exit.c \
		termi.c \
		history.c \
		history_util.c \
		termcap.c \
		termcap2.c \
		input_util.c \
		input_util2.c \
		unset_except.c

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
