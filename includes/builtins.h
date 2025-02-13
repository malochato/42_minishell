/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:39 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 17:31:16 by malde-ch         ###   ########.fr       */
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
int		array_size(char **array);
void	free_array(char **array);
char	**copy_array(char **array, int size);
void free_split(char **split);


// EXPORT UTILS
void	selection_sort(char **array, int size);
int check_valide_export(char *str);

#endif

