/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 16:41:59 by malde-ch         ###   ########.fr       */
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
		return (NULL);
	}
	return (ft_mattstr_copy(ret));
}

static void	handle_dollar_expansion(t_mini *ms, t_token *token)
{
	char	*temp;

	temp = token->cmd;
	token->cmd = expand(ms, token->cmd, ms->envp);
	if (token->cmd == NULL)
		token->cmd = temp;
	else
		temp = free_ptr(temp);
}

static void	handle_tilde_expansion(t_mini *ms, t_token *token)
{
	char	*temp;
	char	*rest;

	temp = token->cmd;
	if (get_env_value(ms->env, "HOME") != NULL)
	{
		rest = ft_strdup(token->cmd + 1);
		token->cmd = expand(ms, "$HOME", ms->envp);
		if (token->cmd == NULL)
			token->cmd = temp;
		else
			temp = free_ptr(temp);
		temp = token->cmd;
		token->cmd = ft_strjoin(temp, rest);
		rest = free_ptr(rest);
		temp = free_ptr(temp);
	}
}

static void	handle_expansion(t_mini *ms, t_token *token)
{
	if (ft_strchr(token->cmd, '$'))
		handle_dollar_expansion(ms, token);
	else if (ft_strchr(token->cmd, '~'))
		handle_tilde_expansion(ms, token);
}

int	expander(t_mini *ms, t_token **head)
{
	t_token	*token;
	char	*temp;

	token = *head;
	while (token)
	{
		handle_expansion(ms, token);
		if (!token->prev || (token->prev && token->prev->type != HEREDOC))
		{
			temp = token->cmd;
			token->cmd = expand_quotes(token->cmd);
			temp = free_ptr(temp);
			if (!token->cmd && !token->prev && !token->next)
				return (1);
		}
		token = token->next;
	}
	return (0);
}
