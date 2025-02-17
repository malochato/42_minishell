/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/17 18:33:40 by malde-ch         ###   ########.fr       */
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





int update_env_var(t_env_var *env, char **split, char *str)
{
    while (env != NULL)
    {
        if (ft_strncmp(env->key, split[0], ft_strlen(env->key)) == 0 && ft_strlen(env->key) == ft_strlen(split[0]))
        {
            if (env->value != NULL)
                free(env->value);
            if (split[1] != NULL)
			{
				ft_strdup(str + ft_strlen(split[0]) + 1);
            }
			else if (str[ft_strlen(str) - 1] == '=')
				env->value = ft_strdup("");
			else
				env->value = NULL;
            return (0);
        }
        env = env->next;
    }
    return (1);
}

int add_env_var(t_mini *mini, char *key, char *value, char *str)
{
	t_env_var *env;
	t_env_var *new;

	printf("add_env_var %s |%s|\n", key, value);
	new = malloc(sizeof(t_env_var));
	if (new == NULL)
	{
		perror("Error with malloc");
		return (1);
	}
	new->key = ft_strdup(key);
	if (value != NULL)
	{
		new->value = ft_strdup(value);
	}
	else if (str[ft_strlen(str) - 1] == '=')
		new->value = ft_strdup("");
	else
		new->value = NULL;
	new->next = NULL;
	env = mini->env;
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	return (0);
}


int add_or_update_env_var(t_mini *mini, char **split, char *str)
{
    if (update_env_var(mini->env, split, str) == 0)
        return (0);

    if (split[1] != NULL)
	{
		add_env_var(mini, split[0], str + ft_strlen(split[0]) + 1, str);
	}
	else
        add_env_var(mini, split[0], NULL, str);

    return (0);
}


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
		// return (handle_export_no_args(mini));
		return_value = handle_export_no_args(mini);
		// regardez s'il y a pas d'erreur.
	}
	if (mini->cmd->cmd[1] != NULL)
	{
		printf("export %s\n", mini->cmd->cmd[1]);
		// si export a un argument
		// on der la variable doit ajout'environnement
		// si elle n'existe pas
		// sinon on doit la modifier

		// de plus ensuite on refait cette action si il y a plusieurs arguments

		return_value = handle_export_args(mini);
	}
	return (return_value);
}
