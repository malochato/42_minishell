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
	int				return_value;
	t_cmd			*cmd;

	init_builtins(builtins);
	return_value = 0;
	cmd = mini->cmd;

	/*
		il va y avoir une boucle sur mini->cmd
		avec un check pour regarder si la commande fait partis des builtins    CHECK
		si oui on execute le builtin											CHECK
		sinon on execute le binaire.
	*/
 	while (cmd)
	{
		if (cmd->cmd[0] == NULL)
			return (0);
		func = get_builtin_func(cmd->cmd[0], builtins);
		if (func)
			return_value = func(mini, cmd);
		else
		{
			printf("Not a builtin\n");
			// Execute binary here
		}
		cmd = cmd->next;
	}

	return (return_value);
}
/* 
	TO DO: 
	execute builtins, 
	

	Un petit plus : 
		si on utilise un bultins 
		mais avec des options executer le binaire

		ca pourrais etre vraiment cool. 

 */