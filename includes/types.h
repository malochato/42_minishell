/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:44:09 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/04 06:41:10 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef enum e_operator
{
	OP_NONE, // 0
	OP_AND, // &&
	OP_OR, // ||
	OP_PIPE, // |
	OP_REDIRECT_OUT, // >
	OP_REDIRECT_OUT_APPEND, // >>
	OP_REDIRECT_IN, // <
	OP_HERE_DOC, // <<
	CMD,
}	t_operator;

typedef struct s_cmd
{
	char		**cmd;
	int			pipe[2];
	int			fd_in;
	int			fd_out;
	t_operator	operator;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_mini
{
	int			exit_status;
	char		**envp;
	t_env_var	*env;
	t_cmd		*cmd;
}	t_mini;


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

#endif