/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 20:40:26 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 20:30:38 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		nbr_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	init_cursor(t_cursor *cursor)
{
	cursor->buf = NULL;
	cursor->cm = tgetstr("cm", NULL);
	cursor->ce = tgetstr("ce", NULL);
	cursor->c = 0;
	cursor->col = 14;
	cursor->listcircle = 1;
	cursor->tmpbuf = NULL;
	cursor->hisbuf = NULL;
	cursor->len = 0;
}

void	get_cursor_position(int *rows)
{
	int		a;
	int		i;
	char	buf[255];
	int		ret;
	int		temp;

	a = 0;
	i = 1;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
				temp = ft_atoi(&buf[i]);
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}
