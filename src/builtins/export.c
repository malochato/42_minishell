/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 05:01:30 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	handle_export_no_args(char **envp)
{
	int			size;
	t_env_var	*env_cpy;
	t_env_var	*tmp;

	env_cpy = create_sorted_list(envp);
	if (env_cpy == NULL)
		return (2);
	tmp = env_cpy;
	size = ft_lstsize_env(env_cpy);
	while (size > 0)
	{
		if (env_cpy->value != NULL)
			printf("declare -x %s=\"%s\"\n", env_cpy->key, env_cpy->value);
		else
			printf("declare -x %s\n", env_cpy->key);
		env_cpy = env_cpy->next;
		size--;
	}
	free_env(tmp);
	return (0);
}

int	export_args(t_mini *mini, char *str)
{
	char		*delimiter_pos;
	char		*key;
	char		*value;

	delimiter_pos = ft_strchr(str, '=');
	if (delimiter_pos != NULL)
	{
		key = ft_strndup(str, delimiter_pos - str);
		if (key == NULL)
			return (2);
		value = ft_strdup(delimiter_pos + 1);
		if (key == NULL)
		{
			free(key);
			return (2);
		}
	}
	else
	{
		key = ft_strdup(str);
		if (key == NULL)
			return (2);
		value = NULL;
	}
	return (env_manager(mini, key, value));
}

int	handle_export_args(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	return_value;

	i = 1;
	return_value = 1;
	while (cmd->cmd[i] != NULL)
	{
		if (check_valide_export(cmd->cmd[i]) == 0)
			return_value = export_args(mini, cmd->cmd[i]);
		if (return_value == 2)
			return (return_value);
		i++;
	}
	return (return_value);
}

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	int	return_value;

	return_value = 0;
	if (cmd->cmd[1] == NULL)
		return_value = handle_export_no_args(mini->envp);
	else if (cmd->cmd[1] != NULL)
		return_value = handle_export_args(mini, cmd);
	return (return_value);
}

// limitations: 
/*

	Limitations que je ne vais pas faire mtn:

	Cas 1. Var1=hola export Var1
	Cas 2. export var1+=hola


	put handle_export_args et export_args dans la meme fonction
*/