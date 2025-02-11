/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:22 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/11 13:50:42 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef enum e_operator
{
    OP_NONE, // 0
    OP_AND, // &&
    OP_OR,  // ||
    OP_PIPE, // |
    OP_REDIRECT_OUT, // >
    OP_REDIRECT_OUT_APPEND, // >>
    OP_REDIRECT_IN, // <
	OP_HERE_DOC, // <<
} t_operator;


typedef struct s_redirection
{
    char *file;
    t_operator type;
} t_redirection;


typedef struct s_cmd
{
	char **cmd;
	t_redirection *input;
	t_redirection *output;
	struct s_cmd *next;
} t_cmd;

typedef struct s_mini
{
    char **envp;
	t_cmd *cmd;
} t_mini;


#endif
