/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:12:23 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 21:42:25 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

char	*append_char(t_cursor cursor)
{
	int		len;
	char	*ret;

	len = ft_strlen(cursor.buf);
	ret = ft_calloc(len + 2, 1);
	ft_memcpy(ret, cursor.buf, len);
	ret[len] = cursor.c;
	ret[len + 1] = 0;
	if (cursor.buf)
		free(cursor.buf);
	return (ret);
}

char	*remove_char(t_cursor cursor)
{
	int		len;
	char	*ret;

	len = ft_strlen(cursor.buf);
	if (len == 0)
		return (cursor.buf);
	if (len != 0)
	{
		ret = ft_calloc(len, 1);
		ft_memcpy(ret, cursor.buf, len);
		ret[len - 1] = 0;
		if (cursor.buf)
			free(cursor.buf);
		return (ret);
	}
	return (cursor.buf);
}

void	firstwall(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		write(1, "Just execute ./minishell\n", 26);
		exit(1);
	}
}

void	print_buf(t_cursor **cursor, char *buf)
{
	int		len;

	len = 0;
	if (buf == NULL)
		return ;
	while (buf[len])
	{
		(*cursor)->col++;
		write(0, &buf[len++], 1);
	}
}

int		key_value(t_cursor cursor)
{
	if (cursor.c == LEFT_ARROW || cursor.c == RIGHT_ARROW ||
		cursor.c == BACKSPACE || cursor.c == UP_ARROW ||
		cursor.c == DOWN_ARROW || cursor.c == CTRLD)
		return (0);
	return (1);
}
