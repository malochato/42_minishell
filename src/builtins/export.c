/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 12:00:34 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_export(t_mini *mini)
{
	printf("env -> %s\n", mini->envp[0]);
	mini->envp[0] = "totoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
	return (0);
}