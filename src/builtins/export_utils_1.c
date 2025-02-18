/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:45:09 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/18 19:40:48 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int update_env_var(t_env_var *env, char *key, char *delimiter_pos)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0 && ft_strlen(env->key) == ft_strlen(key))
		{
			if (env->value != NULL)
			{
				free(env->value);
				env->value = NULL;
			}
			if (delimiter_pos == NULL)
			{
				env->value = NULL;
				return (0);
			}
			env->value = ft_strdup(delimiter_pos + 1);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int add_env_var(t_mini *mini, char *key, char *delimiter_pos)
{
	t_env_var *new;
	t_env_var *current;

	new = malloc(sizeof(t_env_var));
	if (new == NULL)
	{
		perror("Error with malloc");
		return (1);
	}
	new->key = ft_strdup(key);
	if (delimiter_pos == NULL)
		new->value = NULL;
	else
		new->value = ft_strdup(delimiter_pos + 1);
	if (new->key == NULL || (delimiter_pos != NULL && new->value == NULL))
	{
		free(new->key);
		free(new->value);
		free(new);
		perror("Error with malloc");
		return (1);
	}
	new->next = NULL;

	if (mini->env == NULL)
	{
		mini->env = new;
	}
	else
	{
		current = mini->env;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return (0);
}


int add_or_update_env_var(t_mini *mini, char *key, char *delimiter_pos)
{
	if (update_env_var(mini->env, key, delimiter_pos) == 0)
	{
		return (0);
	}
	add_env_var(mini, key, delimiter_pos);
	return (0);
}


int export_args(t_mini *mini, char *str)
{
	int		result;
	char		*delimiter_pos;
	char		*key;

	delimiter_pos = ft_strchr(str, '=');
	printf("delimiter_pos: %s\n", delimiter_pos);
	if (delimiter_pos != NULL)
	{
		key = ft_strndup(str, delimiter_pos - str);
		result = add_or_update_env_var(mini, key, delimiter_pos);
		free(key);
	}
	else
	{
		result = add_or_update_env_var(mini, str, NULL);
	}
	return (result);
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
			//ft_strlcat(temp, "=", ft_strlen(env->key) + 2);
			mini->envp[i] = temp;
		}
		i++;
		env = env->next;
	}
	mini->envp[i] = NULL;
}
 