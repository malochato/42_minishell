/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:39 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 10:17:15 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "exec.h"

typedef int (*builtin_func)(t_mini *);

typedef struct s_builtin
{
    char *name;
    builtin_func func;
} t_builtin;

int builtin_pwd(t_mini *mini);
/* int builtin_cd(t_mini *mini);
int builtin_echo(t_mini *mini);
int builtin_exit(t_mini *mini);
int builtin_env(t_mini *mini);
int builtin_setenv(t_mini *mini);
int builtin_unsetenv(t_mini *mini); */

void init_builtins(t_builtin *builtins);
builtin_func get_builtin_func(const char *name, t_builtin *builtins);


#endif

