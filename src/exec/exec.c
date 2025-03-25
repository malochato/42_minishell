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

t_cmd	*go_to_next_cmd(t_cmd *cmd)
{
	while (cmd && cmd->operator != OP_PIPE)
	{
		cmd = cmd->next;
	}
	if (cmd && cmd->operator == OP_PIPE)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

/* int	exec(t_mini *mini)
{
	t_builtin		builtins[8];
	t_builtin_func	func;
	int				exit_status;
	t_cmd			*cmd;

	init_builtins(builtins);
	exit_status = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->cmd[0] == NULL)
			return (mini->exit_status);
		exit_status = prepare_cmd(mini, cmd);
		if (exit_status)
		{
			mini->exit_status = exit_status;
			close_all_fd(cmd);
			break ;
		}
		func = get_builtin_func(cmd->cmd[0], builtins);
		if (func)
			exit_status = execute_builtins(mini, cmd, func);
		else
		{
			exit_status = update_to_absolute_path(mini, cmd);
			if (exit_status == 0)
				exit_status = execute_command(mini, cmd);
		}
		mini->exit_status = exit_status;
		cmd = go_to_next_cmd(cmd);
		remove_file(mini, ".tmp_here_doc");
	}
	return (exit_status);
} */

int	execute_single_command(t_mini *mini, t_cmd *cmd, t_builtin *builtins)
{
	t_builtin_func	func;
	int				exit_status;

	if (cmd->cmd[0] == NULL)
		return (mini->exit_status);
	exit_status = prepare_cmd(mini, cmd);
	if (exit_status)
	{
		mini->exit_status = exit_status;
		close_all_fd(cmd);
		return (exit_status);
	}
	func = get_builtin_func(cmd->cmd[0], builtins);
	if (func)
		exit_status = execute_builtins(mini, cmd, func);
	else
	{
		exit_status = update_to_absolute_path(mini, cmd);
		if (exit_status == 0)
			exit_status = execute_command(mini, cmd);
	}
	mini->exit_status = exit_status;
	return (exit_status);
}

int	exec(t_mini *mini)
{
	t_builtin	builtins[8];
	t_cmd		*cmd;
	int			exit_status;

	init_builtins(builtins);
	exit_status = 0;
	cmd = mini->cmd;
	while (cmd)
	{
		exit_status = execute_single_command(mini, cmd, builtins);
		if (exit_status)
			break ;
		cmd = go_to_next_cmd(cmd);
		remove_file(mini, ".tmp_here_doc");
	}
	return (exit_status);
}
