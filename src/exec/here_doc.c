/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:35:06 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/04 21:15:29 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	remove_file(t_mini *mini, char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (unlink(file) == -1)
			ft_exit(mini, 1, "unlink failed");
	}
}

void	write_here_doc(t_mini *mini, t_cmd *cmd, char *delimiter)
{
	char	*line;

	cmd->fd_in = open(".tmp_here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_in == -1)
		ft_exit(mini, 1, "open .tmp_here_doc for writing failed");
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 \
					&& ft_strlen(line) == ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, cmd->fd_in);
		ft_putstr_fd("\n", cmd->fd_in);
		free(line);
	}
	close(cmd->fd_in);
}

int	handle_here_doc(t_mini *mini, t_cmd *cmd, t_cmd *op)
{
	if (op->operator == OP_HERE_DOC)
	{
		if (is_syntax_error(op))
			return (2);
		write_here_doc(mini, cmd, op->next->cmd[0]);
		cmd->fd_in = open(".tmp_here_doc", O_RDONLY);
		if (cmd->fd_in == -1)
			ft_exit(mini, 1, "open .tmp_here_doc for reading failed");
	}
	return (0);
}
