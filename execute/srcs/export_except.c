/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_except.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/16 15:19:29 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		quo_mark(char *export_cmd, int i)
{
	char	*content;

	content = NULL;
	if (export_cmd[i] == '!' && export_cmd[i + 1] != '\0')
	{
		content = ft_strchr(export_cmd, '!');
		return (cmd_error(content, 2));
	}
	else if (export_cmd[i] == '!' && export_cmd[i + 1] == '\0')
		return (cmd_error(export_cmd, 1));
	return (0);
}

int		cmd_error(char *cmd, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("hyochanyoung: export: ", 2);
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
	else if (error == 2)
	{
		ft_putstr_fd("hyochanyoung: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": event not found\n", 2);
	}
	return (1);
}

int		except_name(int str, int i)
{
	if ((i == 0) && (ft_isalpha(str) < 1) && (str != '_'))
		return (1);
	else if ((i == 0) && ((str == '=') || (str == ' ')))
		return (1);
	else if ((i >= 1) && (ft_isalpha(str) < 1)
		&& (str != '_') && (ft_isdigit(str) < 1) && (str == '!'))
		return (1);
	else if ((i >= 1) && (str == ' '))
		return (1);
	return (0);
}

int		last_check(char *export_cmd, int i)
{
	if (export_cmd[i] != '\0')
	{
		while (export_cmd[i + 1] != '\0')
		{
			if (quo_mark(export_cmd, i))
				return (1);
			i++;
		}
	}
	return (0);
}

int		except_check(char *export_cmd, int type)
{
	int		i;

	i = -1;
	while (export_cmd[++i] != '\0')
	{
		if (type == 1)
			if ((export_cmd[i] == '=') && i != 0)
				break ;
		if (export_cmd[i] == '!' && export_cmd[i + 1] != '=' &&
			export_cmd[i + 1] != '\0')
			return (quo_mark(export_cmd, i));
		else if (export_cmd[i] == '!' && export_cmd[i + 1] == '=')
			return (cmd_error(export_cmd, 1));
		else if (export_cmd[i] == '=' && export_cmd[i + 1] == '!')
			return (quo_mark(export_cmd, i));
		if (except_name(export_cmd[i], i))
		{
			if (quo_mark(export_cmd, i))
				return (1);
			return (cmd_error(export_cmd, 1));
		}
	}
	if (last_check(export_cmd, i))
		return (1);
	return (0);
}
