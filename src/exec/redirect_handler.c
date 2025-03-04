/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:31:48 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/04 18:49:07 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_redirect_out(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	if (op->operator == OP_REDIRECT_OUT)
	{
		if (op->next == NULL)
		{
			ft_exit(mini, 1, "syntax error near unexpected token");
		}
		cmd->fd_out = open(op->next->cmd[0], \
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			ft_exit(mini, 1, "Error opening file");
		return (3);
	}
	return (0);
}

int	handle_redirect_out_append(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	if (op->operator == OP_REDIRECT_OUT_APPEND)
	{
		if (op->next == NULL)
		{
			ft_exit(mini, 1, "syntax error near unexpected token");
		}
		cmd->fd_out = open(op->next->cmd[0], \
						O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			ft_exit(mini, 1, "Error opening file");
		return (3);
	}
	return (0);
}

int	handle_redirect_in(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	if (op->operator == OP_REDIRECT_IN)
	{
		if (op->next == NULL)
		{
			ft_exit(mini, 1, "syntax error near unexpected token");
		}
		cmd->fd_in = open(op->next->cmd[0], O_RDONLY);
		if (cmd->fd_in == -1)
			ft_exit(mini, 1, "Error opening file");
		return (3);
	}
	return (0);
}

int	handle_pipe(t_mini *mini, t_cmd *cmd_cpy, t_cmd *op)
{
	t_cmd	*cmd_next;
	int		pipe_fd[2];

	cmd_next = op->next;
	if (cmd_cpy->fd_out != -1)
	{
		// this is when you already have a outpout file
		//allez a la fin de la liste
		return (1);
	}
	if (pipe(pipe_fd) == -1)
		ft_exit(mini, 1, "Error creating pipe");
	cmd_next->fd_in = pipe_fd[0];
	cmd_cpy->fd_out = pipe_fd[1];
	return (1);
}