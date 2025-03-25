/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:29:19 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/25 23:12:33 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd(t_cmd **cmd_list, char *cmd_str)
{
	t_cmd	*new_cmd;
	t_cmd	*temp;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->cmd = ft_calloc(2, sizeof(char *));
	new_cmd->cmd[0] = ft_strdup(cmd_str);
	new_cmd->cmd[1] = NULL;
	new_cmd->next = NULL;
	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		temp = *cmd_list;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_cmd;
	}
}

static int	is_buildin(char *cmd)
{
	char	**list;
	int		i;

	list = ft_calloc(8, sizeof(char *));
	if (!list)
		return (-1);
	list[0] = ft_strdup("echo");
	list[1] = ft_strdup("cd");
	list[2] = ft_strdup("pwd");
	list[3] = ft_strdup("export");
	list[4] = ft_strdup("unset");
	list[5] = ft_strdup("env");
	list[6] = ft_strdup("exit");
	list[7] = NULL;
	i = -1;
	while (list[++i])
	{
		if (!ft_strncmp(cmd, list[i], ft_strlen(list[i])))
		{
			list = free_mat(list);
			return (1);
		}
	}
	list = free_mat(list);
	return (0);
}

void	define_cmd_type(t_cmd *cmd, char *cmd_str)
{
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	if (!ft_strncmp(cmd_str, "|", 1))
		cmd->operator = OP_PIPE;
	else if (!ft_strncmp(cmd_str, ">>", 2))
		cmd->operator = OP_REDIRECT_OUT_APPEND;
	else if (!ft_strncmp(cmd_str, ">", 1))
		cmd->operator = OP_REDIRECT_OUT;
	else if (!ft_strncmp(cmd_str, "<<", 2))
		cmd->operator = OP_HERE_DOC;
	else if (!ft_strncmp(cmd_str, "<", 1))
		cmd->operator = OP_REDIRECT_IN;
	else if (is_buildin(cmd_str))
		cmd->operator = BUILTIN;
	else
		cmd->operator = OP_NONE;
}

void	create_cmd_list(t_mini *ms)
{
	t_cmd	*current_cmd;
	char	**cmd_lexer;
	int		i;

	i = 0;
	cmd_lexer = token_to_mat(ms->token);
	if (!cmd_lexer || !cmd_lexer[0])
		return ;
	ms->cmd = NULL;
	while (cmd_lexer[i])
	{
		add_cmd(&ms->cmd, cmd_lexer[i]);
		current_cmd = ms->cmd;
		while (current_cmd->next != NULL)
		{
			current_cmd = current_cmd->next;
		}
		define_cmd_type(current_cmd, cmd_lexer[i]);
		i++;
	}
	cmd_lexer = free_mat(cmd_lexer);
}
