/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:29:19 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/25 15:57:50 by dalara-s         ###   ########.fr       */
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

// void parser(t_mini *ms, char *str)
// {
//     char **cmd_lexer;
// 	t_token **head;
// 	head = &ms->token;
//     cmd_lexer = lexer(str);
//     if(!cmd_lexer)
//     {
//         ft_putstr_fd("-minishell: parser: unclosed quotes\n", 2);
//         free_mat(cmd_lexer);
//         return ;//error message quotes
//     }
//     fill_token(head, cmd_lexer);
//     define_type(head);
//     int i =-1;
//     char *temp = NULL;
//     while(cmd_lexer[++i])
//     {
//         check_sep(cmd_lexer[i]);
//         temp = lexer_quotes(cmd_lexer[i]);
//         printf("cmd_lexer[%d]: %s\n", i, temp);
//         temp = free_ptr(temp);
//     }
//     create_cmd_list(&ms->cmd, cmd_lexer);	
//     free_mat(cmd_lexer);
//    // free_ptr(tem
// }