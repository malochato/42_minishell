/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:49:04 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/20 19:42:40 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_unset(t_mini *mini)
{
	int	i;

	i = 1;
	while (mini->cmd->cmd[i] != NULL)
		remove_env_var(mini, mini->cmd->cmd[i++]);
	return (0);
}
