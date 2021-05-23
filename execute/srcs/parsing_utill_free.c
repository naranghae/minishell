/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:44 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/23 17:25:25 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	free_split(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (ft_strlen(s[i])!=0)
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_red(t_red **red)
{
	t_red *nod;
	t_red *next;

	nod = *red;
	while (nod != NULL)
	{
		next = nod->next;
		if (nod->file_name != NULL)
			free(nod->file_name);
		free(nod);
		nod = next;
	}
	free(nod);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd *nod;
	t_cmd *next;

	(*cmd)->tail->next = NULL;
	(*cmd)->tail = NULL;
	free((*cmd)->tail);
	nod = *cmd;
	while (nod != NULL)
	{
		printf ("1\n");
		// if (nod->next == NULL)
		// 	break ;
		next = nod->next;
		if (nod->red != NULL)
			free_red(&(nod->red));
		if (nod->cmd != NULL)
			free_split(nod->cmd);
		nod = NULL;
		free(nod);
		nod = next;
	}
	free(nod);
}
