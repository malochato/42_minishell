/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:39:29 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 04:15:53 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*create_env_string(t_mini *mini, t_env_var *env)
{
	char	*temp;

	if (env->value != NULL)
	{
		temp = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
		if (temp == NULL)
			ft_exit(mini, 1, "malloc");
		ft_strlcpy(temp, env->key, ft_strlen(env->key) + 1);
		ft_strlcat(temp, "=", ft_strlen(temp) + 2);
		ft_strlcat(temp, env->value, ft_strlen(temp) + \
		ft_strlen(env->value) + 1);
	}
	else
	{
		temp = malloc(ft_strlen(env->key) + 1);
		if (temp == NULL)
			ft_exit(mini, 1, "malloc");
		ft_strlcpy(temp, env->key, ft_strlen(env->key) + 1);
	}
	return (temp);
}

void	fill_env_array(t_mini *mini)
{
	t_env_var	*env;
	int			i;

	i = 0;
	env = mini->env;
	while (env != NULL)
	{
		mini->envp[i] = create_env_string(mini, env);
		i++;
		env = env->next;
	}
	mini->envp[i] = NULL;
}

void	update_env_array(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->envp != NULL)
		free_split(mini->envp);
	i = ft_lstsize_env(mini->env);
	mini->envp = malloc((i + 1) * sizeof(char *));
	if (mini->envp == NULL)
		ft_exit(mini, 1, "malloc");
	fill_env_array(mini);
}
