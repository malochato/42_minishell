/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:31:52 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/17 18:39:32 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*create_env_var(char *env_entry)
{
	t_env_var	*new_var;
	char		*delimiter_pos;

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
	{
		perror("malloc");
		return (NULL);
	}
	delimiter_pos = ft_strchr(env_entry, '=');
	if (!delimiter_pos)
	{
		free(new_var);
		return (NULL);
	}
	new_var->key = ft_strndup(env_entry, delimiter_pos - env_entry);
	new_var->value = ft_strdup(delimiter_pos + 1);
	new_var->next = NULL;
	return (new_var);
}

void	free_env(t_env_var *env_var)
{
	t_env_var	*head;
	t_env_var	*current;

	head = env_var;
	if (!head)
		return ;
	while (head)
	{
		current = head;
		head = head->next;
		free(current->key);
		//if (current->value)
		free(current->value);
		free(current);
	}
}

t_env_var	*parser_env(char **env)
{
	t_env_var	*head;
	t_env_var	*current;
	t_env_var	*new_var;
	int			i;

	head = NULL;
	current = NULL;
	i = 0;
	while (env[i])
	{
		new_var = create_env_var(env[i]);
		if (!new_var)
			free_env(head);
		if (!head)
			head = new_var;
		else
			current->next = new_var;
		current = new_var;
		i++;
	}
	return (head);
}
