/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/25 19:25:01 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_quotes(char *cmd)
{
	int		i;
	int		quotes;
	char	**ret;

	i = -1;
	quotes = 0;
	while (cmd[++i])
	{
		quotes = check_quotes(cmd[i], quotes);
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !quotes)
			cmd[i] = SEP;
		else if ((cmd[i] == '\'' && quotes == 2) || \
		(cmd[i] == '\"' && quotes == 1))
			cmd[i] = SEP;
	}
	ret = ft_split(cmd, SEP);
	if (!*ret)
	{
		ret = free_mat(ret);
		return (ft_strdup(""));
	}
	return (ft_mattstr_copy(ret));
}

void	expander(t_mini *ms, t_token **head)
{
	char	*temp;
	t_token	*token;

	token = *head;
	while (token)
	{
		if (ft_strchr(token->cmd, '$'))
		{
			temp = token->cmd;
			token->cmd = expand(ms, token->cmd, ms->envp);
			if (token->cmd == NULL)
				token->cmd = temp;
			else
				temp = free_ptr(temp);
		}
		if (!token->prev || (token->prev && token->prev->type != HEREDOC))
		{
			temp = token->cmd;
			token->cmd = expand_quotes(token->cmd);
			temp = free_ptr(temp);
		}
		token = token->next;
	}
}
