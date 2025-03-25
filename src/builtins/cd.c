/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:12:46 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/25 23:46:17 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	update_pwd(t_mini *mini)
{
	char	*pwd;
	char	*oldpwd;

	if (get_env_value(mini->env, "PWD") != NULL)
	{
		oldpwd = ft_strdup(get_env_value(mini->env, "PWD"));
		if (oldpwd == NULL)
			ft_exit(mini, 1, "malloc");
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			ft_exit(mini, 1, "getcwd");
		env_manager(mini, ft_strdup("PWD"), pwd);
		env_manager(mini, ft_strdup("OLDPWD"), oldpwd);
	}
	else
		remove_env_var(mini, "OLDPWD");
	return (0);
}

int	cd_no_arg(t_mini *mini, t_cmd *cmd)
{
	if (get_env_value(mini->env, "HOME") == NULL)
		return (ft_error("cd", "HOME not set", NULL, 0));
	if (*(char *)get_env_value(mini->env, "HOME") == '\0')
		return (0);
	if (chdir(get_env_value(mini->env, "HOME")) == -1)
		return (ft_error("cd", cmd->cmd[1], NULL, 1));
	return (update_pwd(mini));
}

int	cd_arg_minus(t_mini *mini, t_cmd *cmd)
{
	if (get_env_value(mini->env, "OLDPWD") == NULL)
		return (ft_error("cd", "OLDPWD not set", NULL, 0));
	if (*(char *)get_env_value(mini->env, "OLDPWD") == '\0')
	{
		printf("\n");
		return (0);
	}
	if (chdir(get_env_value(mini->env, "OLDPWD")) == -1)
		return (ft_error("cd", cmd->cmd[1], NULL, 1));
	return (update_pwd(mini));
}

int	cd_arg_path(t_mini *mini, t_cmd *cmd)
{
	if (chdir(cmd->cmd[1]) == -1)
		return (ft_error("cd", cmd->cmd[1], NULL, 1));
	return (update_pwd(mini));
}

int	builtin_cd(t_mini *mini, t_cmd *cmd)
{
	if (cmd->cmd[1] == NULL)
		return (cd_no_arg(mini, cmd));
	else if (cmd->cmd[2] != NULL)
		return (ft_error("cd", "too many arguments", NULL, 0));
	else if (ft_strncmp(cmd->cmd[1], "-", 2) == 0 && \
			ft_strlen(cmd->cmd[1]) == 1)
		return (cd_arg_minus(mini, cmd));
	else
		return (cd_arg_path(mini, cmd));
}

/*
==========================CD=====================

CD without arg


all good need only the expand of ~ 
and all of $var

GOOD !!!

*/
