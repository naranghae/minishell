/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:05:34 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/17 16:43:00 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

void	exec_cd(t_cmd *exec_cmd)
{
	//printf("%s\n", exec_cmd->cmd[1]);
	char buf[1024];

	if (exec_cmd->has_pip)
		if (pipe(exec_cmd->fd) < 0)
			exit(0);
	getcwd(buf, 1024);
	if(chdir(exec_cmd->cmd[1]) == -1)
		printf("failed, cd\n");
}