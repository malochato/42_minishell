/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:44:09 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/25 21:39:00 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

enum e_type
{
	PIPE = 10,
	EXECVE = 11,
	BUILDIN = 12,
	ARG = 13,
	ARG_FILE = 14,
	REDIRECT = 15,
	HEREDOC = 16
};

typedef struct s_token
{
	char			*cmd;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_expand
{
	char	**hold_str;
	int		ex;
	int		start;
	int		end;
	int		quotes;
	int		ex_n;
	int		i;
}	t_expand;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef enum e_operator
{
	OP_NONE, // 0
	BUILTIN, // 1
	OP_PIPE, // |
	OP_REDIRECT_OUT, // >
	OP_REDIRECT_OUT_APPEND, // >>
	OP_REDIRECT_IN, // <
	OP_HERE_DOC, // <<
	OPERATOR,
}	t_operator;

typedef struct s_cmd
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	t_operator		operator;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_mini
{
	int			exit_status;
	char		**envp;
	t_token		*token;
	t_cmd		*cmd;
	t_env_var	*env;
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

typedef int	(*t_handler_func)(t_mini *mini, t_cmd *cmd, t_cmd *op);

typedef struct s_handler
{
	t_operator		operator;
	t_handler_func	func;
}	t_handler;

#endif