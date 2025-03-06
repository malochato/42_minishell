/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:31:52 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/06 18:10:47 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*create_env_var(char *env_entry)
{
	t_env_var	*new_var;
	char		*delimiter_pos;

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
	{
		perror("malloc");
		return (NULL);
	}
	delimiter_pos = ft_strchr(env_entry, '=');
	if (!delimiter_pos)
	{
		new_var->key = ft_strdup(env_entry);
		new_var->value = NULL;
		new_var->next = NULL;
		return (new_var);
	}
	new_var->key = ft_strndup(env_entry, delimiter_pos - env_entry);
	new_var->value = ft_strdup(delimiter_pos + 1);
	new_var->next = NULL;
	return (new_var);
}

char	**duplicate_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	new_env = malloc((i + 1) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		new_env[i] = strdup(envp[i]);
		if (new_env[i] == NULL)
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**default_env(void)
{
	char		**default_env;

	default_env = malloc(3 * sizeof(char *));
	if (!default_env)
		return (NULL);
	default_env[0] = ft_strdup \
	("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	default_env[1] = ft_strdup("TERM=xterm-256color");
	default_env[2] = NULL;
	return (default_env);
}

t_env_var	*create_env_list(char **env_dup)
{
	t_env_var	*head;
	t_env_var	*current;
	t_env_var	*new_var;
	int			i;

	head = NULL;
	current = NULL;
	i = 0;
	while (env_dup[i])
	{
		new_var = create_env_var(env_dup[i]);
		if (!new_var)
		{
			free_env(head);
			return (NULL);
		}
		if (!head)
			head = new_var;
		else
			current->next = new_var;
		current = new_var;
		i++;
	}
	return (head);
}

t_env_var	*parser_env(char **env)
{
	t_env_var	*head;
	char		**env_dup;

	if (!env || !env[0])
		env_dup = default_env();
	else
		env_dup = duplicate_env(env);
	if (!env_dup)
		return (NULL);
	head = create_env_list(env_dup);
	free_split(env_dup);
	return (head);
}
