/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:49:04 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 04:50:16 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_unset(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i] != NULL)
		remove_env_var(mini, cmd->cmd[i++]);
	return (0);
}
