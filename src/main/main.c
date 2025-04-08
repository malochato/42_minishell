/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/08 10:29:08 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_it(t_mini *ms, char *input)
{
	if (parser(ms, input) == 2)
		return ;
	if ((expander(ms, &ms->token) == 1))
		return ;
	create_cmd_list(ms);
	exec(ms);
}

int	main_loop(t_mini *mini)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		setup_signals();
		prompt = get_prompt();
		input = readline(prompt);
		if (input == NULL)
			ft_exit(mini, mini->exit_status, "exit");
		mini->exit_status = update_exit_status(-1);
		if (*input)
		{
			add_history(input);
			do_it(mini, input);
			free_all_parsing(mini);
			free_cmd(mini->cmd);
			mini->cmd = NULL;
			mini->exit_status = update_exit_status(-1);
		}
		free(input);
		free(prompt);
		prompt = NULL;
	}
	return (mini->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		exit_status;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
		ft_exit(mini, 1, "ERROR malloc");
	mini->cmd = NULL;
	mini->exit_status = update_exit_status(-42);
	mini->env = parser_env(envp);
	mini->token = NULL;
	if (!mini->env)
		ft_exit(mini, 1, "ERROR malloc");
	mini->envp = duplicate_env(envp);
	init_shell_env(mini);
	exit_status = main_loop(mini);
	rl_clear_history();
	free_all(mini);
	return (exit_status);
}
