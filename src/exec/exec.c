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
	t_builtin_func	func;
	int				return_value;
	t_cmd			*cmd;

	init_builtins(builtins);
	return_value = 0;
	cmd = mini->cmd;
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
			printf("Executing biinaire\n");
		}
		cmd = cmd->next;
	}
	return (return_value);
}
/* 
	TO DO: 
	execute builtins, CHECK
	launch binaries NEXT BRANCH !!

 */