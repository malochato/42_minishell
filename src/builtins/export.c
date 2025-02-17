/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/17 18:57:45 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int handle_export_no_args(t_mini *mini)
{
	t_env_var *env;
	int size;

	env = mini->env;
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
			export_args(mini, mini->cmd->cmd[i]);
		i++;
	}

	return (0);
}

int builtin_export(t_mini *mini)
{
	int return_value;
	// si export est le seul token
	if (mini->cmd->cmd[1] == NULL)
	{
		return_value = handle_export_no_args(mini);
		// regardez s'il y a pas d'erreur.
	}
	if (mini->cmd->cmd[1] != NULL)
	{
		printf("export %s\n", mini->cmd->cmd[1]);
		return_value = handle_export_args(mini);
		//regardez s'il y a pas d'erreur.
	}
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