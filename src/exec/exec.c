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

static void	handle_child_status(t_mini *mini, int status)
{
	if (WIFEXITED(status))
	{
		update_exit_status(WEXITSTATUS(status));
		mini->exit_status = update_exit_status(-1);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
	{
		update_exit_status(WTERMSIG(status) + 128);
		mini->exit_status = update_exit_status(-1);
	}
}

void	wait_for_all_children(t_mini *mini, t_cmd *cmd, t_builtin *builtins)
{
	int	status;
	int	waited_pid;
	int	child_count;

	child_count = count_children(cmd, builtins);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handle_signal);
	while (child_count > 0)
	{
		waited_pid = waitpid(-1, &status, 0);
		if (waited_pid == -1)
			ft_exit(mini, 1, "waitpid failed");
		child_count--;
		handle_child_status(mini, status);
	}
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

static int	process_command(t_mini *mini, t_cmd *cmd, t_builtin *builtins)
{
	int	exit_status;

	exit_status = 0;
	while (cmd)
	{
		if (!get_builtin_func(cmd->cmd[0], builtins))
			exit_status = update_to_absolute_path(mini, cmd);
		if (exit_status != 0)
		{
			mini->exit_status = exit_status;
			update_exit_status(exit_status);
			break ;
		}
		cmd = go_to_next_cmd(cmd);
	}
	return (exit_status);
}

int	exec(t_mini *mini)
{
	t_builtin	builtins[8];
	t_cmd		*cmd;
	int			exit_status;

	init_builtins(builtins);
	cmd = mini->cmd;
	exit_status = process_command(mini, cmd, builtins);
	if (exit_status == 0)
	{
		while (cmd)
		{
			update_exit_status(execute_single_command(mini, cmd, builtins));
			cmd = go_to_next_cmd(cmd);
			remove_file(mini, ".tmp_here_doc");
		}
		wait_for_all_children(mini, mini->cmd, builtins);
	}
	close_all_fd_list(mini->cmd);
	return (exit_status);
}
