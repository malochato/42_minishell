/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:41:37 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 05:06:04 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	swap_node_env(t_env_var *env_0, t_env_var *env_1)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = env_0->key;
	tmp_value = env_0->value;
	env_0->key = env_1->key;
	env_0->value = env_1->value;
	env_1->key = tmp_key;
	env_1->value = tmp_value;
}

t_env_var	*sort_env(t_env_var *env)
{
	t_env_var	*tmp;

	tmp = env;
	while (env->next != NULL)
	{
		if (ft_strncmp(env->key, env->next->key, ft_strlen(env->key) + 1) > 0)
		{
			swap_node_env(env, env->next);
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

t_env_var	*create_sorted_list(char **envp)
{
	t_env_var	*env_cpy;

	env_cpy = parser_env(envp);
	if (env_cpy == NULL)
		return (NULL);
	env_cpy = sort_env(env_cpy);
	return (env_cpy);
}

int	check_valide_export(char *str)
{
	int	i;

	if (str == NULL || str[0] == '=' || ft_isdigit(str[0]))
		return (ft_error("export", "not a valid identifier", str, 0));
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ft_error("export", "not a valid identifier", str, 0));
		i++;
	}
	return (0);
}
