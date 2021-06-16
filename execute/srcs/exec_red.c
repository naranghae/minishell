/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:26:22 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/15 16:43:15 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		exec_redirection_in_out(t_red **tmp)
{
	if ((*tmp)->type == IN)
	{
		if (((*tmp)->fd = open((*tmp)->file_name, O_RDONLY, 0644)) == -1)
			return (0);
		if (dup2((*tmp)->fd, 0) < 0)
			return (-1);
	}
	else if ((*tmp)->type == OUT)
	{
		if (((*tmp)->fd = open((*tmp)->file_name,
			O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
			return (0);
		if (dup2((*tmp)->fd, 1) < 0)
			return (-1);
	}
	else if ((*tmp)->type == APPEND)
	{
		if (((*tmp)->fd = open((*tmp)->file_name,
			O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
			return (0);
		if (dup2((*tmp)->fd, 1) < 0)
			return (-1);
	}
	return (1);
}

int		exec_redirection(t_cmd *exec_cmd)
{
	t_red	*tmp;
	int		re;

	tmp = exec_cmd->red;
	while (tmp != NULL)
	{
		re = exec_redirection_in_out(&tmp);
		if (re == 0 || re == -1)
		{
			ft_putstr_fd("hyochanyoung: ", 2);
			ft_putstr_fd(tmp->file_name, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
