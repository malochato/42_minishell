/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:45:09 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 02:36:42 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	update_env_var(t_env_var *env, char *key, char *value)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0 && \
			ft_strlen(env->key) == ft_strlen(key))
		{
			if (env->value != NULL)
			{
				free(env->value);
				env->value = NULL;
			}
			free(env->key);
			env->key = key;
			env->value = value;
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int	add_env_var(t_mini *mini, char *key, char *value)
{
	t_env_var	*new;
	t_env_var	*current;

	new = malloc(sizeof(t_env_var));
	if (new == NULL)
		return (2);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (mini->env == NULL)
		mini->env = new;
	else
	{
		current = mini->env;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return (0);
}

int	ft_lstsize_env(t_env_var *env)
{
	int			i;
	t_env_var	*tmp;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
