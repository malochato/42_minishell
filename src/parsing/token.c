/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:02:14 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/13 21:47:04 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	fill_token(t_token **head, char **cmd_lexer)
{
	int		i;

	i = 0;
	while (cmd_lexer[i])
	{
		//printf("IMPORTANTE%s\n", cmd_lexer[i]);
		insert_token(head, cmd_lexer[i]);
		i++;
	}
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
