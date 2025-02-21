/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:32:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 02:34:21 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_env_value(t_env_var *env, char *key)
{
	t_env_var	*current;

	current = env->next;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0 && \
			ft_strlen(current->key) == ft_strlen(key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	is_new_env_var(t_env_var *env, char *key)
{
	t_env_var	*current;

	current = env->next;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0 && \
			ft_strlen(current->key) == ft_strlen(key))
			return (0);
		current = current->next;
	}
	return (1);
}

int	remove_env_var(t_mini *mini, char *str)
{
	t_env_var	*tmp;
	t_env_var	*prev;

	tmp = mini->env;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(str)) == 0 && \
			ft_strlen(str) == ft_strlen(tmp->key))
		{
			if (prev == NULL)
				mini->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			update_env_array(mini);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	env_manager(t_mini *mini, char *key, char *value)
{
	int		result;

	if (is_new_env_var(mini->env, key))
		result = add_env_var(mini, key, value);
	else
		result = update_env_var(mini->env, key, value);
	if (result == 2)
		return (2);
	update_env_array(mini);
	return (result);
}
