/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:07:52 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 15:57:37 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_command(char **paths, char *cmd)
{
	char	*absolute_path;
	char	*tmp;
	int		i;

	i = 0;
	absolute_path = NULL;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		absolute_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(absolute_path, F_OK | X_OK) == 0)
			return (absolute_path);
		free(absolute_path);
		absolute_path = NULL;
		i++;
	}
	return (NULL);
}

char	**split_path(char *path)
{
	char	**split;

	split = ft_split(path, ':');
	if (!split)
		ft_exit(NULL, 1, "malloc");
	return (split);
}

char	*get_path_dirs(t_env_var *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0 && ft_strlen(env->key) == 4)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_absolute_path(t_env_var *env, char *cmd)
{
	char	*path;
	char	**split;
	char	*absolute_path;

	path = get_path_dirs(env);
	if (!path)
		return (NULL);
	split = split_path(path);
	absolute_path = find_command(split, cmd);
	free_split(split);
	return (absolute_path);
}

int	update_to_absolute_path(t_mini *mini, t_cmd *cmd)
{
	char		*absolute_path;
	struct stat	buf;

	if (access(cmd->cmd[0], F_OK | X_OK) == 0)
	{
		stat(cmd->cmd[0], &buf);
		if (S_ISDIR(buf.st_mode))
		{
			ft_error(cmd->cmd[0], "is a directory", NULL, 0);
			return (126);
		}
		return (0);
	}
	absolute_path = get_absolute_path(mini->env, cmd->cmd[0]);
	if (absolute_path == NULL)
	{
		ft_error("command not found", cmd->cmd[0], NULL, 0);
		return (127);
	}
	free(cmd->cmd[0]);
	cmd->cmd[0] = absolute_path;
	return (0);
}
