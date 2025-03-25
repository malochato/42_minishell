/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:09:10 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/25 21:53:16 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_env(t_env_var *env_var)
{
	t_env_var	*head;
	t_env_var	*current;

	head = env_var;
	if (!head)
		return ;
	while (head)
	{
		current = head;
		head = head->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd != NULL)
		{
			free_split(tmp->cmd);
			tmp->cmd = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_all(t_mini *mini)
{
	if (mini == NULL)
		return ;
	if (mini->cmd != NULL)
	{
		close_all_fd_list(mini->cmd);
		free_cmd(mini->cmd);
		mini->cmd = NULL;
	}
	if (mini->env != NULL)
	{
		free_env(mini->env);
		mini->env = NULL;
	}
	if (mini->envp != NULL)
	{
		free_split(mini->envp);
		mini->envp = NULL;
	}
	if (mini->token != NULL)
	{
		free_token(mini->token);
		mini->token = NULL;
	}
	free(mini);
	mini = NULL;
}
