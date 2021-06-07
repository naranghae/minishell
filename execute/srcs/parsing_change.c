/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 202idx/05/11 17:32:19 by chanykim          #+#    #+#             */
/*   Updated: 2021/05/12 11:58:31 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int		find_end(t_cmd *cmd, int idx, int i)
{
	int	re;

	i++;
	while (cmd->cmd[idx][i] != '\0' && cmd->cmd[idx][i] != ' ' && cmd->cmd[idx][i] != '$'&& cmd->cmd[idx][i] != '"')
		i++;
	re = i;
	// printf("reeeeee:%d\n",re);
	return (re);
}

char	*find_env(t_cmd *cmd, t_env *env, int idx, int *i)
{
	t_env	*tmp;
	int		end;
	int		start;

	start = *i + 1;
	end = find_end(cmd, idx, *i);
	tmp = env->next;
	// printf("s:%d,e:%d\n",start,end);
	while(tmp != NULL)
	{
		if (!ft_strncmp(&cmd->cmd[idx][*i], tmp->name, end - start + 1))
		{
			// printf("find : %s key :: %s find: %d  end :%d\n",&cmd->cmd[idx][*i], tmp->name, end-start, end);
			*i += ft_strlen(tmp->name);
			return(tmp->contents);
		}
		tmp = tmp->next;
	}
	// *i = end - 1;
	// printf("retrun12312312\n");
	return (0);
}

void	change_env(t_cmd *tmp, t_env *env, int idx, int i)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	char *envstr;
	int start;

	while (tmp->cmd[idx][i] != '\0')
	{
		if (tmp->cmd[idx][i] == '\\')
		{
			if (tmp->cmd[idx][i++ + 1] != '\0')
				i += 1;
			continue ;
		}
		// printf("c:%c sing:%d\n",tmp->cmd[idx][i],!in_singlequote(tmp->cmd[idx],i,ft_strlen(tmp->cmd[idx])));
		if (tmp->cmd[idx][i++] == '$' && !in_singlequote(tmp->cmd[idx],i,ft_strlen(tmp->cmd[idx])))
		{
			start = i;
			envstr = find_env(tmp, env, idx, &i);
			// printf("envstr:%s\n",envstr);
			if (envstr != 0)
			{
				tmp->cmd[idx] = ft_strjoin(ft_strjoin(ft_substr(tmp->cmd[idx], 0, start - 1), envstr),ft_strdup(&(tmp->cmd[idx][i])));
				i = (start - 1) + ft_strlen(envstr);
				// printf("33333start:%d, end::%d s:%s\n",start,find_end(tmp,idx,start) - start, tmp->cmd[idx]);
			}
			else
			{
				tmp->cmd[idx] = ft_strjoin(ft_substr(tmp->cmd[idx], 0, start - 1), ft_strdup(&(tmp->cmd[idx][find_end(tmp,idx,start)])));
				//  printf("44444start:%d, end::%d s:%s\n",start,find_end(tmp,idx,start) - start, tmp->cmd[idx]);
				 i = (start - 1);
			}
			//echo "$HOME$ASDASDFGA"
		}
	}
}

void	change_escape(t_cmd **cmd, int idx, int start)
{
	char	*re;
	int		re_i;
	t_cmd	*tmp;

	tmp = *cmd;
	re_i = 0;
	re = tmp->cmd[idx];
	while (tmp->cmd[idx][start] != '\0')
	{
		if (tmp->cmd[idx][start] == '\\')
		{
				if (tmp->cmd[idx][start + 1] != '\0' && (tmp->cmd[idx][start + 1] == '`' || tmp->cmd[idx][start + 1] == '$' || tmp->cmd[idx][start + 1] == '"' || tmp->cmd[idx][start + 1] == '\\' /*|| tmp->cmd[idx][start + 1] == '\''*/))
				{
					re[re_i++] = tmp->cmd[idx][start + 1];
					start += 2;
				}
				else
					re[re_i++] = tmp->cmd[idx][start++];
			continue ;
		}
		else
			re[re_i++] = tmp->cmd[idx][start];
		start++;
	}
	re[re_i] = '\0';
	// printf("reeeeeee:%s\n", re);
	(*cmd)->cmd[idx] = re;
}

void	change_double_qute(t_cmd *tmp, int idx, int i)
{
	int start;
	int end;

	while (tmp->cmd[idx][i] != '\0')
	{
		// printf("insigel:%d caric:%c\n", in_singlequote(tmp->cmd[idx],i,ft_strlen(tmp->cmd[idx])), tmp->cmd[idx][i]);
		if (!in_singlequote(tmp->cmd[idx],i,ft_strlen(tmp->cmd[idx])) && tmp->cmd[idx][i] == '\"')
			{
				tmp->cmd[idx][i++] = '\0';
				start = i;
				while (tmp->cmd[idx][i] != '\0' && tmp->cmd[idx][i] != '\"')
					i++;
				if (tmp->cmd[idx][i] == '\0' && start == i)
				{
					tmp->cmd[idx][i-1] = '"';
					// printf("54321 start:%d,i:%d,s:%s",start,i,tmp->cmd[idx]);
					return ;
				}
				if (tmp->cmd[idx][i] != '\0' && i > 1 && tmp->cmd[idx][i] =='\"' && tmp->cmd[idx][i] == '\\')
				{
					// printf("123123123erfsdfdfv\n");
					tmp->cmd[idx][i - 1] = '9';
					break ;
				}
				if (tmp->cmd[idx][i] != '\0')
				{
					end = i;
					tmp->cmd[idx][end] = '\0';
					tmp->cmd[idx] = ft_strjoin(tmp->cmd[idx],ft_strjoin(tmp->cmd[idx] + start, tmp->cmd[idx] + end + idx));
					i = end - 1;
					continue ;
				}
				else
					break ;
			}
		i++;
	}
}

void change_single_qute(t_cmd *tmp, int idx, int i)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	int start;
	int end;

	while (tmp->cmd[idx][i] != '\0')
	{
		//printf("i : %d, 2c:%c 2sing:%d\n",i,tmp->cmd[idx][i],!in_singlequote(tmp->cmd[idx],i,ft_strlen(tmp->cmd[idx])));
		if (tmp->cmd[idx][i] == '\'' && tmp->cmd[idx][i + 1] != '\0')
			{
				tmp->cmd[idx][i++] = '\0';
				if (i > 1 && tmp->cmd[idx][i - 2] == '\\')
				{
					tmp->cmd[idx][i - 2] = '\'';
					break ;
				}
				start = i;
				while (tmp->cmd[idx][i] != '\0' && tmp->cmd[idx][i] != '\'')
					i++;
				if (tmp->cmd[idx][i] != '\0')
				{
					end = i;
					tmp->cmd[idx][end] = '\0';
					tmp->cmd[idx] = ft_strjoin(tmp->cmd[idx],ft_strjoin(tmp->cmd[idx] + start, tmp->cmd[idx] + end + idx));
					i = end - 1;
					continue ;
				}
				// else
				// {
				// 	tmp->cmd[idx][start - 2] = '\'';
				// 	break ;
				// }
			}
		i++;
	}
}

void change_single_qute_in_double(t_cmd *tmp, int idx, int i)// 추후에 또 나눠야함 cmd[0]도 사실은 변환시켜야하고 해서 여기서는 리스트만 돌면서 함수두개 반복케
{
	int start;
	int end;

	while (tmp->cmd[idx][i] != '\0')
	{
		// printf("2c:%c 2sing:%d\n",tmp->cmd[idx][i],!in_singlequote(tmp->cmd[idx],i,ft_strlen(tmp->cmd[idx])));
		if (in_doublequote(tmp->cmd[idx], i, ft_strlen(tmp->cmd[idx])) && tmp->cmd[idx][i] == '\'')
			{
				tmp->cmd[idx][i++] = '\0';
				start = i;
				while (tmp->cmd[idx][i] != '\0' && tmp->cmd[idx][i] != '\'')
					i++;
				if (tmp->cmd[idx][i] != '\0')
				{
					end = i;
					tmp->cmd[idx][end] = '\0';
					tmp->cmd[idx] = ft_strjoin(tmp->cmd[idx],ft_strjoin(tmp->cmd[idx] + start, tmp->cmd[idx] + end + idx));
					i = end - 1;
					continue ;
				}
				else
					break ;
			}
		i++;
	}
}

void change_qute(t_cmd **list, t_env *env,int type)
{
	int idx;
	int i;
	t_cmd *tmp;

	// if (type == 1)
	// 	tmp = (*list)->next;
	// else
		tmp = *list;
	while (tmp != tmp->tail)
	{
		idx = 0;
		while (tmp->cmd[idx]!= NULL)
		{
			i = 0;
			if (type == 1)
			{
				change_single_qute(tmp, idx, i);
			}
			else if (type == 2)
			{
				change_env(tmp, env, idx, i);
				change_double_qute(tmp, idx, i);
				change_escape(&tmp, idx, i);
				change_single_qute(tmp, idx, i);
			}
			idx++;
		}
		tmp = tmp->next;
	}
}
