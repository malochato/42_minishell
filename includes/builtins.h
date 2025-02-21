/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:39 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 05:52:38 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "exec.h"
# include "env.h"

/* 
	Cela est un alias de la fonction builtin
	Elles ont toutes la meme signature
	et donc cela permet de les stocker dans un tableau
	et de les appeler de maniere dynamique
	avec un pointeur de fonction.
 */
typedef int	(*t_builtin_func)(t_mini *, t_cmd *cmd);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}	t_builtin;

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
