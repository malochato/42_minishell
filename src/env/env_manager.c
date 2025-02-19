/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:32:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 22:12:50 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int is_new_key(t_env_var *env, char *key)
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

int env_manager(t_mini *mini, char *key, char *value)
{
	int		result;
	
	if (is_new_key(mini->env, key))
	{
		result = add_env_var(mini, key, value);
	}
	else
	{
		result = update_env_var(mini->env, key, value);
	}
	if (result == 2)
		return (2);
	update_env_array(mini);
	return (result);
}
