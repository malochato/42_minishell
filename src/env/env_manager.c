/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:32:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 21:38:23 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int env_manager(t_mini *mini, char *key, char *value)
{
	int		result;

	result = update_env_var(mini->env, key, value);
	if (result == 0)
		return (0);
	result = add_env_var(mini, key, value);
	update_env_array(mini);
	return (result);
}
