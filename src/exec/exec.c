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
/*
nous utilisons des opérations bit à bit pour vérifier si le processus enfant s'est terminé normalement 
et pour obtenir son code de sortie. 
Le masque 0x7F est utilisé pour vérifier si le processus s'est terminé normalement, 
et le décalage de bits >> 8 suivi du masque 0xFF est utilisé pour obtenir le code de sortie.
Similaire a la macro WIFEXITED(status) de wait.h
*/
int	check_exit_status(t_mini *mini, int status)
{
	int exit_status;
	int term_signal;

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

int execute_command(t_mini *mini, char **cmd, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		ft_exit(mini, 1, "fork failed");
	else if (pid == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			ft_exit(mini, 1, "execve failed");
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			ft_exit(mini, 1, "waitpid failed");

		return (check_exit_status(mini, status));
	}
	return (-42);
}


int	exec(t_mini *mini)
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
			return (0);
		func = get_builtin_func(cmd->cmd[0], builtins);
		if (func)
			exit_status = func(mini, cmd);
		else
		{
			printf("Executing binaire\n");
			exit_status = update_to_absolute_path(mini, cmd);
			if (exit_status == 0)
				exit_status = execute_command(mini, cmd->cmd, mini->envp);
			
		}
		mini->exit_status = exit_status;
		cmd = cmd->next;
	}
	return (exit_status);
}
/* 
	TO DO: 
	execute builtins, CHECK
	launch binaries NEXT BRANCH !!

 */