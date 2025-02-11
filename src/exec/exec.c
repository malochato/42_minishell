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

	printf("mini->cmd = %s\n", mini->cmd->cmd[0]);


	printf("You entered in exec\n");

	/*
		il va y avoir une boucle sur mini->cmd
		avec un check pour regarder si la commande fait partis des builtins
		si oui on execute le builtin
		sinon on execute le binaire.
	*/


	return (0);
}