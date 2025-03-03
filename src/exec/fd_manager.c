/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:28:03 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/03 23:46:34 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	prepare_execution(t_cmd *cmd, t_shell *shell)
{
	int		ret;

	ret = 0;
	if (cmd->type == CMD_SIMPLE)
	{
		if (cmd->simple_cmd->argv[0] == NULL)
			return (0);
		if (is_builtin(cmd->simple_cmd->argv[0]))
			ret = exec_builtin(cmd->simple_cmd, shell);
		else
			ret = exec_bin(cmd->simple_cmd, shell);
	}
	else if (cmd->type == CMD_PIPE)
		ret = exec_pipe(cmd, shell);
	else if (cmd->type == CMD_REDIR)
		ret = exec_redir(cmd, shell);
	return (ret);
}