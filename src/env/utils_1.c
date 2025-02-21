/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:39:29 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/20 23:21:19 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"


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
		//printf("key and value : %s %s\n", env->key, env->value);
        if (env->value != NULL)
        {
            temp = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
            if (temp == NULL)
            {
                perror("Error with malloc");
                return;
            }
            ft_strlcpy(temp, env->key, ft_strlen(env->key) + 1);
            ft_strlcat(temp, "=", ft_strlen(temp) + 2);
            ft_strlcat(temp, env->value, ft_strlen(temp) + ft_strlen(env->value) + 1);
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
            mini->envp[i] = temp;
        }
        i++;
        env = env->next;
    }
    mini->envp[i] = NULL;
}

