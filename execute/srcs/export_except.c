/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_except.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/10 15:32:50 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		quo_mark(char *export_cmd, int i)
{
	int		error;
	char	*content;

	content = NULL;
	if (export_cmd[i] == '!')
	{
		error = 2;
		content = ft_strchr(export_cmd, '!');
		return (cmd_error(content, error));
	}
	return (0);
}

int		cmd_error(char *cmd, int error)
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

int		except_name(int str, int i)
{
	if ((i == 0) && (ft_isalpha(str) < 1) && (str != '_'))
		return (1);
	else if ((i >= 1) && (ft_isalpha(str) < 1)
		&& (str != '_') && (ft_isdigit(str) < 1))
		return (1);
	else if (str == '!')
		return (2);
	return (0);
}

int		except_check(char *export_cmd, int type)
{
	int		i;
	int		error;

	error = 0;
	i = -1;
	while (export_cmd[++i] != '\0')
	{
		if (type == 1)
			if ((export_cmd[i] == '=') && i != 0)
				break ;
		if (export_cmd[i] == '!')
		{
			error = 2;
			return (cmd_error(export_cmd, error));
		}
		if (except_name(export_cmd[i], i))
		{
			error = 1;
			if (quo_mark(export_cmd, i))
				return (2);
			return (cmd_error(export_cmd, error));
		}
	}
	while (export_cmd[i] != '\0')
	{
		if (quo_mark(export_cmd, i))
			return (2);
		i++;
	}
	return (0);
}
