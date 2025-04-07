/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:31:48 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 22:29:41 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_syntax_error(t_cmd *op)
{
	if (op->next == NULL || op->next->cmd == NULL \
		|| op->next->operator == OP_PIPE \
		|| op->next->operator == OP_REDIRECT_IN \
		|| op->next->operator == OP_REDIRECT_OUT \
		|| op->next->operator == OP_REDIRECT_OUT_APPEND \
		|| op->next->operator == OP_HERE_DOC)
	{
		if (op && op->next && op->next->cmd)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(op->next->cmd[0], 2);
			ft_putstr_fd("'\n", 2);
			remove_file(NULL, op->next->cmd[0]);
		}
		else
		{
			ft_putstr_fd \
			("minishell: syntax error near unexpected token `newline'\n", 2);
		}
		return (1);
	}
	return (0);
}

int	handle_redirect_out(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	if (op->operator == OP_REDIRECT_OUT)
	{
		if (is_syntax_error(op))
			return (2);
		cmd->fd_out = open(op->next->cmd[0], \
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			ft_exit(mini, 1, "Error opening / creating file");
	}
	return (0);
}

int	handle_redirect_out_append(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	if (op->operator == OP_REDIRECT_OUT_APPEND)
	{
		if (is_syntax_error(op))
			return (2);
		cmd->fd_out = open(op->next->cmd[0], \
						O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			ft_exit(mini, 1, "Error opening / creating file");
	}
	return (0);
}

int	handle_redirect_in(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	if (op->operator == OP_REDIRECT_IN)
	{
		if (is_syntax_error(op))
			return (2);
		if (access(op->next->cmd[0], F_OK) == -1)
		{
			ft_error(op->next->cmd[0], "No such file or directory", NULL, 0);
			return (1);
		}
		cmd->fd_in = open(op->next->cmd[0], O_RDONLY);
		if (cmd->fd_in == -1)
			ft_exit(mini, 1, "Error opening file");
	}
	return (0);
}

/* 	
	if (cmd_cpy->fd_out != -1) 
	this is when you already have a outpout file descriptor
*/

int	handle_pipe(t_mini *mini, t_cmd *cmd_cpy, t_cmd *op)
{
	t_cmd	*cmd_next;
	int		pipe_fd[2];

	if (is_syntax_error(op))
		return (2);
	cmd_next = op->next;
	if (pipe(pipe_fd) == -1)
		ft_exit(mini, 1, "Error creating pipe");
	if (cmd_cpy->fd_out != -1)
	{
		cmd_next->fd_in = pipe_fd[0];
		close(pipe_fd[1]);
		return (0);
	}
	cmd_next->fd_in = pipe_fd[0];
	cmd_cpy->fd_out = pipe_fd[1];
	return (0);
}
