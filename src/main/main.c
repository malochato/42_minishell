/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/25 18:33:45 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void do_it(t_mini *ms, char *input, char **envp)
{
			if (parser(ms, input) == 2){
				return ;
			}
			expander(ms, &ms->token, envp);
			create_cmd_list(ms);
			//print_cmd(ms);
			exec(ms);
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

int update_exit_status(int value)
{
	static int	status;
	int			tmp;

	if (value == -42)
	{
		status = 0;
		return (status);
	}
	if (value == -1)
		return (status);
	tmp = status;
	status = value;
	return (tmp);
}



void	handle_signal(int signal)
{
	char	*prompt;

    if (signal == SIGINT)
    {
		rl_replace_line("", 0);
		rl_redisplay();
        update_exit_status(130);
        write(STDOUT_FILENO, "\n", 1);
		prompt = get_prompt();
		write(STDOUT_FILENO, prompt, ft_strlen(prompt));
		free(prompt);
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
	mini->exit_status = update_exit_status(-42);
	mini->env = parser_env(envp);
	mini->token = NULL;
	
	if (!mini->env)
	{
		ft_exit(mini, 1, "ERROR malloc");
	}

	mini->envp = duplicate_env(envp);
	shell_init(mini);



	while (1)
	{
		mini->exit_status = update_exit_status(-1);
		prompt = get_prompt();
		input = readline(prompt);
		if (input == NULL)
			ft_exit(mini, mini->exit_status, "exit");
		if (*input)
		{
			add_history(input);
			mini->exit_status = update_exit_status(-1);
			do_it(mini, input, envp);
			
			free_all_parsing(mini);
			free_cmd(mini->cmd);
			mini->cmd = NULL;
			mini->exit_status = update_exit_status(mini->exit_status);
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
