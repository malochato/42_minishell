/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:39 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 04:28:23 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "exec.h"
# include "env.h"

typedef int	(*builtin_func)(t_mini *, t_cmd *cmd);

typedef struct s_builtin
{
	char			*name;
	builtin_func	func;
}	t_builtin;

int		builtin_pwd(t_mini *mini, t_cmd *cmd);
int		builtin_unset(t_mini *mini, t_cmd *cmd);
int		builtin_cd(t_mini *mini, t_cmd *cmd);
int		builtin_echo(t_mini *mini, t_cmd *cmd);
int		builtin_exit(t_mini *mini, t_cmd *cmd);
int		builtin_env(t_mini *mini, t_cmd *cmd);
int		builtin_export(t_mini *mini, t_cmd *cmd);


/* int		builtin_pwd(t_mini *mini);
int		builtin_unset(t_mini *mini);
int		builtin_cd(t_mini *mini);
int		builtin_echo(t_mini *mini);
int		builtin_exit(t_mini *mini);
int		builtin_env(t_mini *mini);
int		builtin_export(t_mini *mini); */


void	init_builtins(t_builtin *builtins);
builtin_func get_builtin_func(const char *name, t_builtin *builtins);

// UTILS
int		ft_error(char *cmd, char *error_type, char *val, int perror_active);

// EXPORT UTILS 0 
int		check_valide_export(char *str);

//EXPORT UTILS 2
t_env_var	*create_sorted_list(char **envp);

#endif
/* 
bien revoir tous cela: 

typedef int (*builtin_func)(t_mini *);

typedef struct s_builtin
{
	char *name;
	builtin_func func;
} t_builtin;

je suis pas tres sur 

*/
