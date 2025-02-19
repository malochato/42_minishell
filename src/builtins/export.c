/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 21:35:39 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	handle_export_no_args(char **envp)
{
	int			size;
	t_env_var	*env;
	t_env_var	*tmp;

	env = create_sorted_list(envp);
	if (env == NULL)
		return (1);
	tmp = env;
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
	free_env(tmp);
	return (0);
}

int export_args(t_mini *mini, char *str)
{
	int		result;
	char		*delimiter_pos;
	char		*key;
	char		*value;

	delimiter_pos = ft_strchr(str, '=');
	printf("delimiter_pos: %s\n", delimiter_pos);

	if (delimiter_pos != NULL)
	{
		key = ft_strndup(str, delimiter_pos - str);
		value = ft_strdup(delimiter_pos + 1);
	}
	else
	{
		key = ft_strdup(str);
		value = NULL;
	}
	result = env_manager(mini, key, value);
	return (result);
}

int	handle_export_args(t_mini *mini)
{
	int	i;

	i = 1;
	while (mini->cmd->cmd[i] != NULL)
	{
		if (check_valide_export(mini->cmd->cmd[i]) == 0)
			export_args(mini, mini->cmd->cmd[i]);
		i++;
	}
	return (0);
}

int	builtin_export(t_mini *mini)
{
	int	return_value;

	return_value = 0;
	if (mini->cmd->cmd[1] == NULL)
		return_value = handle_export_no_args(mini->envp);
	else if (mini->cmd->cmd[1] != NULL)
		return_value = handle_export_args(mini);
	return (return_value);
}

// limitations: 
/*

	Limitations que je ne vais pas faire mtn:

	Cas 1. Var1=hola export Var1
	Cas 2. export var1+=hola


	put handle_export_args et export_args dans la meme fonction
*/