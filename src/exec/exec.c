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
	t_builtin		builtins[8];
	builtin_func	func;

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
		printf("|\n");
		func(mini);
		printf("\n|\n");
		
	}
	else
	{
		printf("Not a builtin\n");
		// Execute binary here
	}

/* 
	TO DO: 
	execute builtins, 
	

	Un petit plus : 
		si on utilise un bultins 
		mais avec des options executer le binaire

		ca pourrais etre vraiment cool. 

 */



	return (0);
}