/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:29:19 by dalara-s          #+#    #+#             */
/*   Updated: 2025/04/04 13:01:34 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	check_pipe(char **cmd, t_mini *ms)
{
	char	*input;
	int		i;

	i = 0;
	input = NULL;
	while (cmd[i] != NULL)
		i++;
	if (!ft_strncmp(cmd[i - 1], "|", 1))
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

	head = &ms->token;
	if (!only_spaces(str))
		cmd_lexer = lexer(str);
	else
		return (2);
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
	check_pipe(cmd_lexer, ms);
	free_mat(cmd_lexer);
	return (0);
}
