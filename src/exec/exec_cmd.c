/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 02:03:00 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 16:21:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_children(t_cmd *cmd, t_builtin *builtins)
{
	int	child_count;

	child_count = 0;
	while (cmd)
	{
		if (cmd->operator == OP_PIPE)
			child_count++;
		if (get_builtin_func(cmd->cmd[0], builtins))
			child_count--;
		cmd = cmd->next;
	}
	return (child_count + 1);
}

void	handle_redirection(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2 fd_in failed");
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 fd_out failed");
		close(cmd->fd_out);
	}
}

int	execute_command(t_mini *mini, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit(mini, 1, "fork failed");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		handle_redirection(cmd);
		close_all_fd_list(cmd);
		if (execve(cmd->cmd[0], cmd->cmd, mini->envp) == -1)
			ft_exit(mini, 1, "execve failed");
	}
	else
	{
		close_all_fd(cmd);
		return (0);
	}
	return (-42);
}

int	execute_builtins(t_mini *mini, t_cmd *cmd, t_builtin_func func)
{
	int	exit_status;
	int	saved_stdout;

	saved_stdout = -1;
	if (cmd->fd_out != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout == -1 || dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_exit(mini, 1, "dup2 failed");
		close(cmd->fd_out);
	}
	exit_status = func(mini, cmd);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return (exit_status);
}

int	execute_single_command(t_mini *mini, t_cmd *cmd, t_builtin *builtins)
{
	t_builtin_func	func;
	int				exit_status;

	exit_status = prepare_cmd(mini, cmd);
	if (exit_status)
	{
		mini->exit_status = exit_status;
		close_all_fd(cmd);
		return (exit_status);
	}
	if (cmd->cmd[0] == NULL)
		return (mini->exit_status);
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
