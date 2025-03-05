/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 02:03:00 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/05 23:44:24 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
nous utilisons des opérations bit à bit pour vérifier si le processus enfant
s'est terminé normalement et pour obtenir son code de sortie. 
Le masque 0x7F est utilisé pour vérifier si le processus s'est terminé 
normalement, et le décalage de bits >> 8 suivi du masque 0xFF est utilisé pour
obtenir le code de sortie.
Similaire a la macro WIFEXITED(status) de wait.h
*/

int	check_exit_status(t_mini *mini, int status)
{
	int	exit_status;
	int	term_signal;

	if ((status & 0x7F) == 0)
	{
		exit_status = (status >> 8) & 0xFF;
		return (exit_status);
	}
	else
	{
		term_signal = status & 0x7F;
		ft_exit(mini, term_signal, "Command terminated by signal");
	}
	return (-42);
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
	int		status;

	pid = fork();
	if (pid == -1)
		ft_exit(mini, 1, "fork failed");
	else if (pid == 0)
	{
		handle_redirection(cmd);
		if (execve(cmd->cmd[0], cmd->cmd, mini->envp) == -1)
			ft_exit(mini, 1, "execve failed");
	}
	else
	{
		close_all_fd(cmd);
		if (waitpid(pid, &status, 0) == -1)
			ft_exit(mini, 1, "waitpid failed");
		return (check_exit_status(mini, status));
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
