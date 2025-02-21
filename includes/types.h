/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:44:09 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 05:45:55 by malde-ch         ###   ########.fr       */
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
}	t_operator;

typedef struct s_redirection
{
	char		*file;
	t_operator	type;
}	t_redirection;

typedef struct s_cmd
{
	char			**cmd;
	t_redirection	*input;
	t_redirection	*output;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_mini
{
	int			exit_status;
	char		**envp;
	t_env_var	*env;
	t_cmd		*cmd;
}	t_mini;

#endif