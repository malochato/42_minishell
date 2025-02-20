/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:12:46 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/20 01:01:56 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	update_pwd(t_mini *mini)
{
	char *pwd;
	char *oldpwd;

	if (get_env_value(mini->env, "PWD") != NULL)
	{
		oldpwd = ft_strdup(get_env_value(mini->env, "PWD"));
		if (oldpwd == NULL)
			return (2);
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			free(oldpwd);
			return (3);
		}
		env_manager(mini, ft_strdup("PWD"), pwd);
		env_manager(mini, ft_strdup("OLDPWD"), oldpwd);
	}
	else
		remove_env_var(mini, "OLDPWD");
	return (0);
}

int cd_no_arg(t_mini *mini)
{
	int return_value;

	return_value = 0;
	if (get_env_value(mini->env, "HOME") == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(get_env_value(mini->env, "HOME")) == -1)
	{
		perror("cd");
		return_value = 1;
	}
	return_value = update_pwd(mini);
	return (return_value);
}

int cd_arg_minus(t_mini *mini)
{
	if (get_env_value(mini->env, "OLDPWD") == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(get_env_value(mini->env, "OLDPWD")) == -1)
	{
		perror("cd");
		return (1);
	}
	return (update_pwd(mini));
}

int	builtin_cd(t_mini *mini)
{
	int return_value;


	return_value = 0;
	if (mini->cmd->cmd[1] == NULL)
		return_value = cd_no_arg(mini);
	else if (ft_strncmp(mini->cmd->cmd[1], "-", 2) == 0 && ft_strlen(mini->cmd->cmd[1]) == 1)
		return_value = cd_arg_minus(mini);
	else
		printf("cd with arg\n");
	return(return_value);
}


/*
==========================CD=====================

CD without arg
return to $HOME
if HOME is not set
error : "bash: cd: HOME not set"
--> change the $? to 1. 

CD with -
return to $OLDPWD 
if OLDPWD is not set
error : "bash: cd: OLDPWD not set"

cd .. 
go back one, need to use getcwd (because PWD can be unset)
you can have ../../../ and more ...

cd . 
ne fait rien 

cd /
va a la racine / 
go the futher back !

cd ~ 
go to /home/user. 
limitations go to another user.

cd 



*/



