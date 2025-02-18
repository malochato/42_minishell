/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:45:09 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/18 16:19:05 by malde-ch         ###   ########.fr       */
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
			{
				free(env->value);
				env->value = NULL;
			}
            if (split[1] != NULL)
			{
				env->value = ft_strdup(str + ft_strlen(split[0]) + 1);
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


void update_env_array(t_mini *mini)
{
	t_env_var *env;
	int i;
	char *temp;

	// Free the old envp if it exists
	if (mini->envp != NULL)
	{
		for (i = 0; mini->envp[i] != NULL; i++)
			free(mini->envp[i]);
		free(mini->envp);
	}

	// Count the number of environment variables
	i = ft_lstsize_env(mini->env);

	// Allocate memory for the new envp
	mini->envp = malloc((i + 1) * sizeof(char *));
	if (mini->envp == NULL)
	{
		perror("Error with malloc");
		return;
	}

	// Fill the new envp with the environment variables
	env = mini->env;
	i = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			temp = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
			if (temp == NULL)
			{
				perror("Error with malloc");
				return;
			}
			ft_strlcpy(temp, env->key, ft_strlen(env->key) + 1);
			printf("temp: %s\n", temp);
			ft_strlcat(temp, "=", ft_strlen(temp) + 2);
			printf("temp: %s\n", temp);
			ft_strlcat(temp, env->value, ft_strlen(env->key) + ft_strlen(env->value) + 2);
			printf("temp: %s\n", temp);
			mini->envp[i] = temp;
		}
		else
		{
			temp = malloc(ft_strlen(env->key) + 1);
			if (temp == NULL)
			{
				perror("Error with malloc");
				return;
			}
			ft_strlcpy(temp, env->key, ft_strlen(env->key) + 1);
			ft_strlcat(temp, "=", ft_strlen(env->key) + 2);
			mini->envp[i] = temp;
		}
		i++;
		env = env->next;
	}
	mini->envp[i] = NULL;
}
 