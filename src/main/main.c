/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/25 14:42:24 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void do_it(t_mini *ms, char *input, char **envp)
{
			parser(ms, input);
			expander(ms, &ms->token, envp);
			create_cmd_list(ms);
			print_cmd(ms);
			//free_all(ms);
}

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

// Désactiver l'écho du signal SIGQUIT
// Désactiver l'écho des caractères de contrôle
void	disable_sigquit_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		ft_exit(NULL, 1, "ERROR with tcgetattr");
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		ft_exit(NULL, 1, "ERROR with tcsetattr");
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// la il faut update le exit status a 130
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;
	int		exit_status;
	char	*prompt;

	(void)argc;
	(void)argv;
	disable_sigquit_echo();
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		ft_exit(NULL, 1, "ERROR with signal");
	if (signal(SIGQUIT, handle_signal) == SIG_ERR)
		ft_exit(NULL, 1, "ERROR with signal");


	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		ft_exit(mini, 1, "ERROR malloc");
	}
	mini->cmd = NULL;
	mini->exit_status = 0;
	mini->env = parser_env(envp);
	mini->token = NULL;
	//ms->exit_status = 42;
	
	if (!mini->env)
	{
		ft_exit(mini, 1, "ERROR malloc");
	}

	mini->envp = duplicate_env(envp);
	shell_init(mini);



	while (1)
	{
		//printf("holi\n");
		prompt = get_prompt(mini);
		input = readline(prompt);
		if (input == NULL)
			ft_exit(mini, mini->exit_status, "exit");
		if (*input)
		{
			add_history(input);
		
			do_it(mini, input, envp);
			//printf("You entered: %s\n", input);
			exec(mini);
			free_all_parsing(mini);
			free_cmd(mini->cmd);
			mini->cmd = NULL;
		}
		free(input);
		free(prompt);
		prompt = NULL;
	}
	exit_status = mini->exit_status;
	rl_clear_history();
	free_all(mini);
	return (exit_status);
}
