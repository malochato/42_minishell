/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:49:04 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 17:07:21 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_if_var_exist(t_env_var **env, char *str)
{
	t_env_var	*tmp;
	t_env_var	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(str)) == 0 && \
			ft_strlen(str) == ft_strlen(tmp->key))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	builtin_unset(t_mini *mini)
{
	int	i;

	i = 1;
	while (mini->cmd->cmd[i] != NULL)
	{
		if (check_if_var_exist(&(mini->env), mini->cmd->cmd[i]))
		{
			printf("Encouter a var to unset");
			update_env_array(mini);
		}
		i++;
	}
	return (0);
}
