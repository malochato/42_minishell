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

int execute_command(t_mini *mini, char **cmd, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{

		// Child process
		print_split(cmd);
		if (access(cmd[0], F_OK | X_OK) == 0)
		{
			if (execve(cmd[0], cmd, envp) == -1)
			{
				perror("execve");
				ft_exit(mini, 1, "execve failed");
			}
		}
		else
		{
			ft_exit(mini, 127, "command not found");
		}
	}
	else
	{
		// Parent process
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (-1);
		}
	}
	return (0);
}


#include "exec.h"

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
				execute_command(mini, cmd->cmd, mini->envp);
			
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