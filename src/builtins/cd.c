/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:12:46 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 20:18:11 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"



int	check_argument(char *arg)
{
	if (arg == NULL)
	{
		printf("bash: cd: HOME not set\n");
		return (1);
	}
	return (0);
}


int	builtin_cd(t_mini *mini)
{
	int return_value;

	(void)mini;
	printf("entering in CD !!");
	return_value = 0;
	if (mini->cmd->cmd[1] == NULL)
	{
		if (check_argument(get_env_value(mini->env, "HOME")))
			return (1);
		if (chdir(get_env_value(mini->env, "HOME")) == -1)
		{
			perror("Error with chdir");
			return_value = 1;
		}
	}
	else
	{
		printf("cd with arg");
	}

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



