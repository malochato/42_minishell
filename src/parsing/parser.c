/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:29:19 by dalara-s          #+#    #+#             */
/*   Updated: 2025/04/01 16:25:08 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_pipe(char *cmd, t_mini *ms)
{
	char	*input;

	input = NULL;
	if (!ft_strncmp(cmd, "|", 2))
	{
		input = readline("> ");
		if (input && !input[0])
		{
			input = free_ptr(input);
			return ;
		}
		parser(ms, input);
		input = free_ptr(input);
	}
}

int	parser(t_mini *ms, char *str)
{
	char	**cmd_lexer;
	t_token	**head;
	int		i;

	head = &ms->token;
	cmd_lexer = lexer(str);
	if (!cmd_lexer)
	{
		ft_putstr_fd("-minishell: parser: unclosed quotes\n", 2);
		free_mat(cmd_lexer);
		return (2);
	}
	fill_token(head, cmd_lexer);
	if (syntax_checker(ms))
	{
		free_mat(cmd_lexer);
		return (2);
	}
	i = 0;
	while (cmd_lexer[i])
		i++;
	check_pipe(cmd_lexer[i - 1], ms);
	free_mat(cmd_lexer);
	return (0);
}
