/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:29:19 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/24 18:34:12 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_cmd(t_cmd **cmd_list, char *cmd_str)
{
	t_cmd *new_cmd = ft_calloc(1, sizeof(t_cmd));
	new_cmd->cmd = split_args(cmd_str);
	new_cmd->next = NULL;

	if (*cmd_list == NULL)
	{
		*cmd_list = new_cmd;
	}
	else
	{
		t_cmd *temp = *cmd_list;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_cmd;
	}
}
void define_cmd_type(t_cmd *cmd, char *cmd_str)
{
	cmd->fd_in = -1;
	cmd->fd_out = -1;

	if (!ft_strncmp(cmd_str, "|", 1)){
		cmd->operator = OP_PIPE;
		printf("pipe");
	}
	else if (!ft_strncmp(cmd_str, ">>", 2)){
		cmd->operator = OP_REDIRECT_OUT_APPEND;
		printf("out_append");
	}
	else if (!ft_strncmp(cmd_str, ">", 1)){
		cmd->operator = OP_REDIRECT_OUT;
		printf("out");
	}
	else if (!ft_strncmp(cmd_str, "<<", 2)){
		cmd->operator = OP_HERE_DOC;
	}
	else if (!ft_strncmp(cmd_str, "<", 1)){
		cmd->operator = OP_REDIRECT_IN;
		printf("in");
	}
	else {
		cmd->operator = OP_NONE;
	}
}

void create_cmd_list(t_mini *ms)
{
	char **cmd_lexer = token_to_mat(ms->token);
	int i = 0;
	if (!cmd_lexer || !cmd_lexer[0])
		return;
	ms->cmd = NULL;
	while (cmd_lexer[i])
	{
		add_cmd(&ms->cmd, cmd_lexer[i]);
		t_cmd *current_cmd = ms->cmd;
		while (current_cmd->next != NULL)
		{
			current_cmd = current_cmd->next;
		}
		define_cmd_type(current_cmd, cmd_lexer[i]);
		printf("%s\n", cmd_lexer[i]);
		i++;
	}
	cmd_lexer = free_mat(cmd_lexer);
}

void	print_cmd(t_mini *ms)
{
	t_cmd	*current_cmd;
	int		cmd_index;

	if (!ms || !ms->cmd) // Verifica se a estrutura ou a l
	{
		printf("No commands to print.\n");
		return;
	}

	current_cmd = ms->cmd;
	cmd_index = 0;

	while (current_cmd)
	{
		char **cmd = current_cmd->cmd;
		int i = 0;
		if (!cmd) // Verifica se há comandos antes
		{
			printf("No commands to print.\n");
		}
		else
		{
			printf("Command %d:\n", cmd_index);
			while (cmd[i])
			{
				printf("cmd[%d][%d]: %s\n", cmd_index, i, cmd[i]);
				i++;
			}
		}

		current_cmd = current_cmd->next;
		cmd_index++;
	}

	if (cmd_index == 0)
	{
		printf("No commands to print.\n");
	}
}
