/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:56:20 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 19:12:45 by malde-ch         ###   ########.fr       */
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
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		update_exit_status(131);
		write(STDOUT_FILENO, "Quit: 3\n", 8);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
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
