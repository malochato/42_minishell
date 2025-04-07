/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:02:14 by dalara-s          #+#    #+#             */
/*   Updated: 2025/04/07 15:22:54 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_buildin(char *token)
{
	char	**list;
	int		i;

	list = ft_calloc(8, sizeof(char *));
	if (!list)
		return (-1);
	list[0] = ft_strdup("echo");
	list[1] = ft_strdup("cd");
	list[2] = ft_strdup("pwd");
	list[3] = ft_strdup("export");
	list[4] = ft_strdup("unset");
	list[5] = ft_strdup("env");
	list[6] = ft_strdup("exit");
	list[7] = NULL;
	i = -1;
	while (list[++i])
	{
		if (!ft_strncmp(token, list[i], ft_strlen(list[i])))
		{
			list = free_mat(list);
			return (1);
		}
	}
	list = free_mat(list);
	return (0);
}

static void	define_type(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
			token->type = PIPE;
		else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)) || \
		!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd)))
			token->type = REDIRECT;
		else if (!ft_strncmp(token->cmd, "<<", ft_strlen("<<")))
			token->type = HEREDOC;
		else if (is_buildin(token->cmd))
			token->type = BUILDIN;
		else if (!token->prev || token->prev->type == PIPE)
			token->type = EXECVE;
		else if (token->prev->type == REDIRECT)
			token->type = ARG_FILE;
		else
			token->type = ARG;
		token = token->next;
	}
}

void	fill_token(t_token **head, char **cmd_lexer)
{
	int		i;

	i = 0;
	while (cmd_lexer[i])
	{
		insert_token(head, cmd_lexer[i]);
		i++;
	}
	define_type(head);
}

void	insert_token(t_token **head, char *token)
{
	t_token	*new;
	t_token	*temp;

	new = ft_calloc(1, sizeof(t_token));
	new->cmd = ft_strdup(token);
	new->type = 0;
	new->prev = NULL;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	new->prev = temp;
	temp->next = new;
}
