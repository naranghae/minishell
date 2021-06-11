/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:26:22 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/11 13:36:47 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		exec_redirection_in_out(t_red **tmp)
{
	if ((*tmp)->type == IN)
	{
		if (!((*tmp)->fd = open((*tmp)->file_name, O_RDONLY, 0644)))
			return (0);
		if (dup2((*tmp)->fd, 0) < 0)
			return (0);
	}
	else if ((*tmp)->type == OUT)
	{
		if (!((*tmp)->fd = open((*tmp)->file_name,
			O_CREAT | O_WRONLY | O_TRUNC, 0644)))
			return (0);
		if (dup2((*tmp)->fd, 1) < 0)
			return (0);
	}
	else if ((*tmp)->type == APPEND)
	{
		if (!((*tmp)->fd = open((*tmp)->file_name,
			O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644)))
			return (0);
		if (dup2((*tmp)->fd, 1) < 0)
			return (0);
	}
	return (1);
}

void	exec_redirection(t_cmd *exec_cmd)
{
	t_red *tmp;

	tmp = exec_cmd->red;
	while (tmp != NULL)
	{
		if (!exec_redirection_in_out(&tmp))
			return ;
		tmp = tmp->next;
	}
}
