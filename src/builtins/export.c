/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 20:25:29 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int handle_export_no_args(t_mini *mini)
{
	int i;
	int size;
	char **tmp;

	char **copy;

	size = array_size(mini->envp);
	tmp = copy_array(mini->envp, size);
	if (tmp == NULL)
	{
		perror("Error with malloc");
		return (1);
	}
	selection_sort(tmp, size);
	i = 0;
	while (tmp[i] != NULL)
	{
		copy = ft_split(tmp[i], '=');
		if (copy == NULL)
		{
			perror("Error with malloc");
			return (1);
		}
		if (copy[1] != NULL)
			printf("declare -x %s=\"%s\"\n", copy[0], tmp[i] + ft_strlen(copy[0]) + 1);
		else
			printf("declare -x %s\n", tmp[i]);
		i++;
		/* 		free_split(copy);
				copy = NULL; */
	}
	free_array(tmp);
	tmp = NULL;
	return (0);
}
int add_element_env(char *str, t_mini *mini)
{
	int size;
	char **new_envp;
	int i;

	size = array_size(mini->envp);
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (new_envp == NULL)
	{
		perror("Error with malloc");
		return (1);
	}
	i = 0;
	while (i < size)
	{
		new_envp[i] = mini->envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(str);
	printf("OUI\n");
	if (new_envp[i] == NULL)
	{
		perror("Error with ft_strdup");
		// free tout les elements de new_envp
		free(new_envp);
		return (1);
	}
	new_envp[i + 1] = NULL;
	free(mini->envp);
	mini->envp = new_envp;
	return (0);
}

int replace_element_env(char *str, t_mini *mini)
{
	int i;
	char **tmp;

	i = 0;
	while (mini->envp[i] != NULL)
	{
		tmp = ft_split(mini->envp[i], '=');
		if (tmp == NULL)
		{
			perror("Error with malloc");
			return (1);
		}
		if (ft_strncmp(tmp[0], str, ft_strlen(str)) == 0)
		{
			free(mini->envp[i]);
			mini->envp[i] = ft_strdup(str);
			if (mini->envp[i] == NULL)
			{
				perror("Error with ft_strdup");
				free_split(tmp);
				return (1);
			}
			free_split(tmp);
			return (0);
		}
		free_split(tmp);
		i++;
	}
	return (1);
}

int is_new_env(char *str, t_mini *mini)
{
	int i;
	char **tmp;

	i = 0;
	while (mini->envp[i] != NULL)
	{
		tmp = ft_split(mini->envp[i], '=');
		if (tmp == NULL)
		{
			perror("Error with malloc");
			return (1);
		}
		printf("tmp[0] = %s\n", tmp[0]);
		if (strstr(mini->envp[i], str) == mini->envp[i] && mini->envp[i][ft_strlen(str)] == '=')
		{
			printf("c'est pas nouveau\n");
			free_split(tmp);
			return (0);
		}
		free_split(tmp);
		i++;
	}
	return (1);
}

int handle_export_args(t_mini *mini)
{
	int i;
/* 	int size;
	char **tmp; */

	i = 1;
	while (mini->cmd->cmd[i] != NULL)
	{
		if (check_valide_export(mini->cmd->cmd[i]) == 0)
		{
			printf("good export\n");
			if (is_new_env(mini->cmd->cmd[i], mini) == 0)
				replace_element_env(mini->cmd->cmd[i], mini);
			else
				add_element_env(mini->cmd->cmd[i], mini);
		}
		else
		{
			printf("bad export\n");
		}
		i++;
	}

	return (0);
}

int builtin_export(t_mini *mini)
{
	// si export est le seul token
	if (mini->cmd->cmd[1] == NULL)
	{
		// return (handle_export_no_args(mini));
		handle_export_no_args(mini);
		// regardez s'il y a pas d'erreur.
	}
	if (mini->cmd->cmd[1] != NULL)
	{
		printf("export %s\n", mini->cmd->cmd[1]);
		// si export a un argument
		// on doit ajouter la variable d'environnement
		// si elle n'existe pas
		// sinon on doit la modifier

		// de plus ensuite on refait cette action si il y a plusieurs arguments

		handle_export_args(mini);
	}
	return (0);
}
