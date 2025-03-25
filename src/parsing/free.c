/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:02:14 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/25 15:52:33 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	**free_mat(char **mat)
{
	size_t	i;

	i = 0;
	while (mat && mat[i])
	{
		mat[i] = free_ptr(mat[i]);
		i++;
	}
	free (mat);
	mat = NULL;
	return (NULL);
}

t_cmd	*free_cmd_parsing(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd->cmd = free_mat (cmd->cmd);
		cmd = cmd -> next;
		free (temp);
	}
	return (NULL);
}

t_token	*free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token -> cmd = free_ptr (token -> cmd);
		token = token -> next;
		free (temp);
	}
	return (NULL);
}

void	free_all_parsing(t_mini *ms)
{
	ms->cmd = free_cmd_parsing(ms->cmd);
	ms->token = free_token(ms->token);
	free(ms->cmd);
	ms->cmd = NULL;
}
