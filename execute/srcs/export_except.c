/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_except.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/26 12:25:07 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		cmdError(char *cmd, int error)
{
	if (error == 1)
	{
		printf("export: '%s' : not a valid identifier\n", cmd);
		return (1);
	}
	else if (error == 2)
	{
		printf("'%s': event not found\n", cmd);
		return (2);
	}
	else
		return (1);
}

int		exceptName(int str, int i)
{
	if ((i == 0) && (ft_isalpha(str) < 1) && (str != '_'))
		return (1);
	else if ((i >= 1) && (ft_isalpha(str) < 1) && (str != '_') && (ft_isdigit(str) < 1))
		return (1);
	else if (str == '!')
		return (2);
	return (0);
}

int		exceptCheck(char *exportCmd)
{
	int		i;
	int		error;

	error = 0;
	i = -1;
	while (exportCmd[++i] != '\0')
	{
		if ((exportCmd[i] == '=') && i != 0)
			break ;
		if (exportCmd[i] == '!')
		{
			error = 2;
			return (cmdError(exportCmd, error));
		}
		if (exceptName(exportCmd[i], i))
		{
			error = 1;
			return (cmdError(exportCmd, error));
		}
	}
	return (0);
}
