/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/18 16:14:30 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int handle_export_no_args(t_env_var *env)
{
	int size;
	
	size = ft_lstsize_env(env);
	while (size > 0)
	{
		if (env->value != NULL)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
		size--;
	}

	return (0);
}
// la fonction est pas encore trier 
// je ferais cela apres quand j'aurais des fonctions pour transformer les listes en tableau


int export_args(t_mini *mini, char *str)
{
    char	**split;
	int		result;

	split = ft_split(str, '=');
    if (*split == NULL)
    {
        perror("Error with malloc");
        return (1);
    }
	result = add_or_update_env_var(mini, split, str);
    free_split(split);
    return result;
}


int handle_export_args(t_mini *mini)
{
	int i;

	i = 1;
	while (mini->cmd->cmd[i] != NULL)
	{
		if (check_valide_export(mini->cmd->cmd[i]) == 0)
		{
			printf("export %s is valid\n", mini->cmd->cmd[i]);
			export_args(mini, mini->cmd->cmd[i]);

		}
		i++;
	}
	update_env_array(mini);
	return (0);
}

int builtin_export(t_mini *mini)
{
	int return_value;
	// si export est le seul token
	return_value = 0;
	if (mini->cmd->cmd[1] == NULL)
	{
		handle_export_no_args(create_sorted_list(mini));
	}
	if (mini->cmd->cmd[1] != NULL)
	{
		printf("export %s\n", mini->cmd->cmd[1]);
		return_value = handle_export_args(mini);
		//regardez s'il y a pas d'erreur.
	}
	printf("last env in array is: %s\n", mini->envp[ft_lstsize_env(mini->env) - 1]);
	return (return_value);
}







// limitations: 
/*
	il faut que je mette en place le tri, !!!!!!!!!!!!!!!!!!


	et en plus je dois mettre en place la fonction qui transforme la liste en tableau
	pour update les variables d'environnement

	Je ne crois pas que le sens dans lequelle sont les variable est important. 



	Limitations que je ne vais pas faire mtn:

	Cas 1. Var1=hola export Var1
	Cas 2. export var1+=hola
*/