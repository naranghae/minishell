/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utill_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:32:44 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 16:48:38 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	free_split(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}

void	free_red(t_red **red)
{
	t_red *next;

	while ((*red) != NULL)
	{
		next = (*red)->next;
		if ((*red)->file_name)
		{
			printf("free!\n");
			free((*red)->file_name);
		}
		printf("free!\n");
		free((*red));
		(*red) = next;
	}
	printf("free!\n");
	free((*red));
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd *next;

	(*cmd)->tail->next = NULL;
	(*cmd)->tail = NULL;
	free((*cmd)->tail);
	while ((*cmd) != NULL)
	{
		next = (*cmd)->next;
		if ((*cmd)->red)
		{
			free_red(&((*cmd)->red));
			free((*cmd)->red);
		}
		if ((*cmd)->cmd)
			free_split((*cmd)->cmd);
		free((*cmd));
		(*cmd) = next;
	}
}
