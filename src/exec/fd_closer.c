/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_closer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:28:03 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/04 16:32:53 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_fd(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

void	close_all_fd(t_cmd *cmd)
{
	close_fd(&cmd->fd_in);
	close_fd(&cmd->fd_out);
}

void	close_all_fd_list(t_cmd *cmd)
{
	while (cmd)
	{
		close_all_fd(cmd);
		cmd = cmd->next;
	}
}
