/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:43:01 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/06 18:52:00 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_directory(t_mini *mini)
{
	char	*pwd;
	char	*home;
	char	*home_replacement;

	pwd = getcwd(NULL, 0);
	home = get_env_value(mini->env, "HOME");
	if (home != NULL && pwd != NULL && \
	ft_strncmp(pwd, home, ft_strlen(home)) == 0)
	{
		home_replacement = ft_strjoin("~", pwd + ft_strlen(home));
		free(pwd);
		pwd = home_replacement;
	}
	return (pwd);
}

char	*get_exit_status_color(int exit_status)
{
	if (exit_status == 0)
		return (COLOR_GREEN);
	else
		return (COLOR_RED);
}

char	*build_prompt(const char *pwd, const char *color, \
					const char *exit_status_str, t_mini *mini)
{
	size_t	prompt_size;
	char	*prompt;

	prompt_size = ft_strlen("minishell: ") + ft_strlen(pwd) + ft_strlen(" [") \
						+ ft_strlen(color) + ft_strlen(exit_status_str) \
						+ ft_strlen(COLOR_RESET) + ft_strlen("] % ") + 1;
	prompt = malloc(prompt_size);
	if (prompt == NULL)
		ft_exit(mini, 1, "ERROR malloc");
	ft_strlcpy(prompt, "minishell: ", prompt_size);
	if (pwd != NULL)
	{
		ft_strlcat(prompt, pwd, prompt_size);
	}
	ft_strlcat(prompt, " [", prompt_size);
	ft_strlcat(prompt, color, prompt_size);
	ft_strlcat(prompt, exit_status_str, prompt_size);
	ft_strlcat(prompt, COLOR_RESET, prompt_size);
	ft_strlcat(prompt, "] % ", prompt_size);
	return (prompt);
}

char	*get_prompt(t_mini *mini)
{
	char	*pwd;
	char	*exit_status_str;
	char	*color;
	char	*prompt;

	pwd = get_current_directory(mini);
	exit_status_str = ft_itoa(mini->exit_status);
	color = get_exit_status_color(mini->exit_status);
	prompt = build_prompt(pwd, color, exit_status_str, mini);
	free(exit_status_str);
	free(pwd);
	return (prompt);
}
