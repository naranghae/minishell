/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_except.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanykim <chanykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:27:51 by chanykim          #+#    #+#             */
/*   Updated: 2021/06/16 15:24:34 by chanykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"
#include "minishell_parsing.h"

int		unset_quo_mark(char *export_cmd, int i)
{
	char	*content;

	content = NULL;
	if (export_cmd[i] == '!' && export_cmd[i + 1] != '\0')
	{
		content = ft_strchr(export_cmd, '!');
		return (unset_error(content, 2));
	}
	else if (export_cmd[i] == '!' && export_cmd[i + 1] == '\0')
		return (unset_error(export_cmd, 1));
	return (0);
}

int		unset_error(char *cmd, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("hyochanyoung: unset: ", 2);
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

int		special_string(char *export_cmd, int i)
{
	if (export_cmd[i] == '!' && export_cmd[i + 1] != '=' &&
		export_cmd[i + 1] != '\0')
		return (unset_quo_mark(export_cmd, i));
	else if (export_cmd[i] == '!' && export_cmd[i + 1] == '=')
		return (unset_error(export_cmd, 1));
	else if (export_cmd[i] == '=' && export_cmd[i + 1] == '!')
		return (unset_quo_mark(export_cmd, i));
	return (0);
}

int		except_unset(char *export_cmd)
{
	int		i;

	i = -1;
	while (export_cmd[++i] != '\0')
	{
		if (export_cmd[i] == '=')
			break ;
		if (special_string(export_cmd, i))
			return (1);
		if (except_name(export_cmd[i], i))
		{
			if (unset_quo_mark(export_cmd, i))
				return (1);
			return (unset_error(export_cmd, 1));
		}
	}
	if (last_check(export_cmd, i))
		return (1);
	if (export_cmd[i] == '=')
		return (unset_error(export_cmd, 1));
	return (0);
}
