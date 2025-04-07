/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:40:50 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 02:33:08 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# include <sys/wait.h>

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

int		exec(t_mini *mini);

//ABSOLUTE_PATH
int		update_to_absolute_path(t_mini *mini, t_cmd *cmd);

//EXEC_CMD
int		count_children(t_cmd *cmd, t_builtin *builtins);
int		execute_command(t_mini *mini, t_cmd *cmd);
int		execute_builtins(t_mini *mini, t_cmd *cmd, t_builtin_func func);
int		execute_single_command(t_mini *mini, t_cmd *cmd, t_builtin *builtins);

//FD_MANAGER
int		prepare_cmd(t_mini *mini, t_cmd *cmd);

//REDIRECT_HANDLER
int		is_syntax_error(t_cmd *op);
int		handle_redirect_out(t_mini *mini, t_cmd *cmd, t_cmd *op);
int		handle_redirect_out_append(t_mini *mini, t_cmd *cmd, t_cmd *op);
int		handle_redirect_in(t_mini *mini, t_cmd *cmd, t_cmd *op);
int		handle_pipe(t_mini *mini, t_cmd *cmd_cpy, t_cmd *op);

//FD_CLOSER
void	close_all_fd_list(t_cmd *cmd);
void	close_all_fd(t_cmd *cmd);

//HERE_DOC
int		handle_here_doc(t_mini *mini, t_cmd *cmd, t_cmd *op);
void	remove_file(t_mini *mini, char *file);

//UTILS
void	append_to_array(t_mini *mini, char ***array, const char *str);

#endif