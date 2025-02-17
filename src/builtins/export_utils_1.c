/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:45:09 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/17 18:45:20 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int update_env_var(t_env_var *env, char **split, char *str)
{
    while (env != NULL)
    {
        if (ft_strncmp(env->key, split[0], ft_strlen(env->key)) == 0 && ft_strlen(env->key) == ft_strlen(split[0]))
        {
            if (env->value != NULL)
                free(env->value);
            if (split[1] != NULL)
			{
				ft_strdup(str + ft_strlen(split[0]) + 1);
            }
			else if (str[ft_strlen(str) - 1] == '=')
				env->value = ft_strdup("");
			else
				env->value = NULL;
            return (0);
        }
        env = env->next;
    }
    return (1);
}

int add_env_var(t_mini *mini, char *key, char *value, char *str)
{
	t_env_var *env;
	t_env_var *new;

	new = malloc(sizeof(t_env_var));
	if (new == NULL)
	{
		perror("Error with malloc");
		return (1);
	}
	new->key = ft_strdup(key);
	if (value != NULL)
	{
		new->value = ft_strdup(value);
	}
	else if (str[ft_strlen(str) - 1] == '=')
		new->value = ft_strdup("");
	else
		new->value = NULL;
	new->next = NULL;
	env = mini->env;
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	return (0);
}


int add_or_update_env_var(t_mini *mini, char **split, char *str)
{
    if (update_env_var(mini->env, split, str) == 0)
        return (0);

    if (split[1] != NULL)
	{
		add_env_var(mini, split[0], str + ft_strlen(split[0]) + 1, str);
	}
	else
        add_env_var(mini, split[0], NULL, str);

    return (0);
}
