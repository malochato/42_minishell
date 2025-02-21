/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 04:51:30 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_mini *mini)
{
	char	*pwd;
	char	*char_shlvl;
	int		shlvl;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_error("error retrieving current directory", "getcwd", \
		NULL, 1));
	env_manager(mini, ft_strdup("PWD"), pwd);
	char_shlvl = get_env_value(mini->env, "SHLVL");
	if (char_shlvl != NULL)
	{
		shlvl = ft_atoi(char_shlvl);
		if (shlvl >= 0)
			char_shlvl = ft_itoa(shlvl + 1);
		else
			char_shlvl = ft_strdup("1");
	}
	else
		char_shlvl = ft_strdup("1");
	env_manager(mini, ft_strdup("SHLVL"), char_shlvl);
	return (0);
}

void	parse_input(t_mini *mini, char *input)
{
	mini->cmd = malloc(sizeof(t_cmd));
	if (mini->cmd == NULL)
	{
		perror("malloc");
		free_all(mini);
		exit(1);
	}
	mini->cmd->cmd = ft_split(input, ' ');
	if (mini->cmd->cmd == NULL)
	{
		mini->cmd->cmd = malloc(sizeof(char *));
		if (mini->cmd->cmd == NULL)
		{
			perror("malloc");
			free_all(mini);
			exit(1);
		}
		mini->cmd->cmd[0] = NULL;
	}
	mini->cmd->next = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		perror("malloc");
		return (1);
	}
	mini->cmd = NULL;
	mini->exit_status = 0;
	mini->env = parser_env(envp);
	if (!mini->env)
	{
		printf("No env: Bye (with love)\n");
		free(mini);
		return (1);
	}
	mini->envp = duplicate_env(envp);
	shell_init(mini);
	while (1)
	{
		input = readline("minishell $>");
		if (input == NULL)
			break ;
		if (*input)
		{
			add_history(input);
		}
		parse_input(mini, input);
		exec(mini);
		printf("You entered: %s\n", input);
		free(input);
		free_cmd(mini->cmd);
		mini->cmd = NULL;
	}
	rl_clear_history();
	free_all(mini);
	return (0);
}
