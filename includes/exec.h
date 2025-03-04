/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:40:50 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/04 06:37:54 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# include <sys/wait.h>



#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int	exec(t_mini *mini);

//ABSOLUTE_PATH
int	update_to_absolute_path(t_mini *mini, t_cmd *cmd);

//EXEC_CMD
int execute_command(t_mini *mini, t_cmd *cmd);
int	execute_builtins(t_mini *mini, t_cmd *cmd, t_builtin_func func);

//FD_MANAGER
int	prepare_cmd(t_mini *mini, t_cmd *cmd);

//FD_CLOSER
void	close_all_fd_list(t_cmd *cmd);
void	close_all_fd(t_cmd *cmd);


#endif