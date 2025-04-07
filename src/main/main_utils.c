/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:56:20 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 02:24:19 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_exit_status(int value)
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
	if (signal == SIGINT)
	{
		update_exit_status(130);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// Désactiver l'écho du signal SIGQUIT
// Désactiver l'écho des caractères de contrôle
void	signal_handler(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		ft_exit(NULL, 1, "ERROR with tcgetattr");
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		ft_exit(NULL, 1, "ERROR with tcsetattr");
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		ft_exit(NULL, 1, "ERROR with signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_exit(NULL, 1, "ERROR with signal");
}

int	init_shell_env(t_mini *mini)
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
