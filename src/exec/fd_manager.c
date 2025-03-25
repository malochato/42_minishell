/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 01:32:30 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/25 21:43:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_handler(t_handler *handler)
{
	handler[0].operator = OP_REDIRECT_OUT;
	handler[0].func = handle_redirect_out;
	handler[1].operator = OP_REDIRECT_OUT_APPEND;
	handler[1].func = handle_redirect_out_append;
	handler[2].operator = OP_REDIRECT_IN;
	handler[2].func = handle_redirect_in;
	handler[3].operator = OP_PIPE;
	handler[3].func = handle_pipe;
	handler[4].operator = OP_HERE_DOC;
	handler[4].func = handle_here_doc;
	handler[5].operator = OP_NONE;
	handler[5].func = NULL;
}

t_handler	get_handler(t_operator operator, t_handler *handler)
{
	int	i;

	i = 0;
	while (handler[i].operator != OP_NONE)
	{
		if (handler[i].operator == operator)
			return (handler[i]);
		i++;
	}
	return (handler[i]);
}

int	prepare_cmd(t_mini *mini, t_cmd *cmd)
{
	t_handler	handler[6];
	t_cmd		*current;
	t_handler	current_handler;
	int			ret;

	init_handler(handler);
	current = cmd->next;
	while (current != NULL && current->operator != OP_PIPE)
	{
		current_handler = get_handler(current->operator, handler);
		if (current_handler.operator != OP_NONE)
		{
			ret = current_handler.func(mini, cmd, current);
			if (ret)
				return (ret);
			current = current->next;
		}
		else
			append_to_array(mini, &cmd->cmd, current->cmd[0]);
		current = current->next;
	}
	if (current != NULL && current->operator == OP_PIPE)
		return (handle_pipe(mini, cmd, current));
	return (0);
}
