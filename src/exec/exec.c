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

void print_split(char **split)
{
	int i = 0;
	printf ("|\n");
	while (split[i])
	{
		printf("%s > ", split[i]);
		i++;
	}
	printf("NULL\n|\n");
}

t_cmd	*go_to_next_pipe(t_cmd *cmd)
{
	while (cmd && cmd->operator != OP_PIPE)
	{
		cmd = cmd->next;
	}
	if (cmd && cmd->operator == OP_PIPE)
	{
		cmd = cmd->next;
	}
	return cmd;
}



int	exec(t_mini *mini)
{
	t_builtin		builtins[8];
		t_builtin_func	func;
	int				exit_status;
	t_cmd			*cmd;
	int				next_cmd;

	init_builtins(builtins);
	exit_status = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->cmd[0] == NULL)
			return (0);
		next_cmd = prepare_cmd(mini, cmd);
		printf("next cmd = %d\n", next_cmd);


		func = get_builtin_func(cmd->cmd[0], builtins);
		if (func)
			exit_status = execute_builtins(mini, cmd, func);
		else
		{
			printf("Executing binaire\n");
			exit_status = update_to_absolute_path(mini, cmd);
			if (exit_status == 0)
				exit_status = execute_command(mini, cmd);
		}
		mini->exit_status = exit_status;
		cmd = go_to_next_pipe(cmd);
		remove_file(mini);
	}
	return (exit_status);
}

/* 
	TO DO: 
	execute builtins, CHECK
	launch binaries NEXT BRANCH !!

 */