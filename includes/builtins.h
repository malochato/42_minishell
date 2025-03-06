/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:39 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/06 18:06:42 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "exec.h"
# include "env.h"

// BUILTINS INIT
void			init_builtins(t_builtin *builtins);
t_builtin_func	get_builtin_func(const char *name, t_builtin *builtins);

// BUILTINS
int				builtin_pwd(t_mini *mini, t_cmd *cmd);
int				builtin_unset(t_mini *mini, t_cmd *cmd);
int				builtin_cd(t_mini *mini, t_cmd *cmd);
int				builtin_echo(t_mini *mini, t_cmd *cmd);
int				builtin_exit(t_mini *mini, t_cmd *cmd);
int				builtin_env(t_mini *mini, t_cmd *cmd);
int				builtin_export(t_mini *mini, t_cmd *cmd);

// UTILS
int				ft_error(char *cmd, char *error_type, char *val, \
				int perror_active);

// EXPORT UTILS
int				check_valide_export(char *str);
t_env_var		*create_sorted_list(char **envp);

#endif
