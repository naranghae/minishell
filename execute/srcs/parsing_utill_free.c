/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:44 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/20 20:58:04 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	free_split(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
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
	while (nod)
	{
		next = nod->next;
		// if (nod->file_name != NULL)
		// 	free(nod->file_name);
		free(nod);
		nod = next;
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd *nod;
	t_cmd *next;

	nod = *cmd;
	while (nod != NULL)
	{
		printf ("1\n");
		next = nod->next;
		// if (nod->red != NULL)
		// 	free_red(&(nod->red));
		free(nod);
		nod = next;
	}
}
