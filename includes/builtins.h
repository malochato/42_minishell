/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:39 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/17 18:46:46 by malde-ch         ###   ########.fr       */
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
/* int builtin_cd(t_mini *mini); */
/* int builtin_echo(t_mini *mini); */
/* int builtin_exit(t_mini *mini); */
int builtin_env(t_mini *mini);
int builtin_export(t_mini *mini);

void init_builtins(t_builtin *builtins);
builtin_func get_builtin_func(const char *name, t_builtin *builtins);


// UTILS
int		ft_lstsize_env(t_env_var *env);
void	free_split(char **split);


// EXPORT UTILS 0 
int		check_valide_export(char *str);

// EXPORT UTILS 1
int add_or_update_env_var(t_mini *mini, char **split, char *str);

#endif

