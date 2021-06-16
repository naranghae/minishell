/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 20:40:26 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/15 16:55:18 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	move_cursor_left(t_cursor *cursor)
{
	if (cursor->col > 14)
		--(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
}

void	move_cursor_right(t_cursor *cursor)
{
	int		len;

	len = ft_strlen(cursor->buf);
	if ((cursor->col) <= (len + 13))
		++(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
}

void	delete_end(t_cursor *cursor)
{
	if (cursor->col > 14)
		--(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}
