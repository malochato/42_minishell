/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:32:30 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/04 04:11:51 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int handle_redirect_out(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	(void)mini;
	if (op->operator == OP_REDIRECT_OUT)
	{
		cmd->fd_out = open(op->next->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			return (1);
		return (3);
	}
	return (0);
}

int handle_redirect_out_append(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	(void)mini;
	if (op->operator == OP_REDIRECT_OUT_APPEND)
	{
		cmd->fd_out = open(op->next->cmd[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			return (1);
		return (3);
	}
	return (0);
}

int handle_redirect_in(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	(void)mini;
	if (op->operator == OP_REDIRECT_IN)
	{
		cmd->fd_in = open(op->next->cmd[0], O_RDONLY);
		if (cmd->fd_in == -1)
		{
			// retrourn une erreur 
			// nom du fichiers: No such file or directory
			// et puis execute le prochain apres le pipe cmd
			return (1);
		}
		return (3);
	}
	return (0);
}

int prepare_cmd(t_mini *mini, t_cmd *cmd)
{
	int next_cmd;
	t_cmd *cmd_cpy;

	next_cmd = 0;
	cmd_cpy = cmd;
	printf("prepare_cmd\n");
	while (cmd->operator != OP_PIPE && cmd->next != NULL)
	{
		printf("entre dans la boucle\n");
		if (handle_redirect_out(mini, cmd_cpy, cmd->next) || \
			handle_redirect_out_append(mini, cmd_cpy, cmd->next) || \
			handle_redirect_in(mini, cmd_cpy, cmd->next))
		{
			next_cmd += 3;
			cmd = cmd->next->next;
		}
		else
		{
			next_cmd += 1;
			cmd = cmd->next;
		}
	}
	if (cmd->operator == OP_PIPE)
	{
		printf("ladies and gentlemen, we got him\n");
	}
	printf("prepare_cmd end\n");
	printf("next_cmd = %d\n", next_cmd);
	if (next_cmd == 0)
		return (1);
	return (next_cmd);
}