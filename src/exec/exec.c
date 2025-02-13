/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:59:02 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/11 10:59:04 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec(t_mini *mini)
{
	t_builtin builtins[8];
	builtin_func func;

	init_builtins(builtins);

	printf("You entered in exec\n");

	/*
		il va y avoir une boucle sur mini->cmd
		avec un check pour regarder si la commande fait partis des builtins    CHECK
		si oui on execute le builtin											CHECK
		sinon on execute le binaire.
	*/


	printf("cmd[0] = %s\n", mini->cmd->cmd[0]);
	if (mini->cmd->cmd[0] == NULL)
		return (0);
	func = get_builtin_func(mini->cmd->cmd[0], builtins);
	if (func)
    {
        func(mini);
    }
    else
    {
        printf("Not a builtin\n");
        // Execute binary here
    }



	return (0);
}