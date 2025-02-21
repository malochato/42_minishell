/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:57:38 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 04:45:02 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(t_mini *mini, t_cmd *cmd)
{
	t_env_var	*env;

	(void)cmd;
	env = mini->env;
	while (env != NULL)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
