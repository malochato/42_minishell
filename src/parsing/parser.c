/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:29:19 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/13 21:38:58 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_buildin(char *token)
{
	char	**list;
	int		i;

	list = ft_calloc(8, sizeof(char *));
	if (!list)
		return (-1);
	list[0] = ft_strdup("echo");
	list[1] = ft_strdup("cd");
	list[2] = ft_strdup("pwd");
	list[3] = ft_strdup("export");
	list[4] = ft_strdup("unset");
	list[5] = ft_strdup("env");
	list[6] = ft_strdup("exit");
	list[7] = NULL;
	i = -1;
	while (list[++i])
	{
		if (!ft_strncmp(token, list[i], ft_strlen(token)))
		{
			list = free_mat(list);
			return (1);
		}
	}
	list = free_mat(list);
	return (0);
}

static void	define_type(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (!ft_strncmp(token->cmd, "|", ft_strlen(token->cmd)))
			token->type = PIPE;
		else if (!ft_strncmp(token->cmd, ">>", ft_strlen(token->cmd)) || \
		!ft_strncmp(token->cmd, "<", ft_strlen(token->cmd)))
			token->type = REDIRECT;
		else if (!ft_strncmp(token->cmd, "<<", ft_strlen("<<")))
			token->type = HEREDOC;
		else if (is_buildin(token->cmd))
			token->type = BUILDIN;
		else if (!token->prev || token->prev->type == PIPE)
			token->type = EXECVE;
		else if (token->prev->type == REDIRECT)
			token->type = ARG_FILE;
		else
			token->type = ARG;
		token = token->next;
	}
}

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

void	parser(t_mini *ms, char *str)
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
		return ;
	}
	fill_token(head, cmd_lexer);
	define_type(head);// mudar para o expander, porque $
	if (syntax_checker(ms))
		exit(2);// fazer funcao pra liberar tudo
	i = 0;
	while (cmd_lexer[i])
		i++;
	check_pipe(cmd_lexer[i - 1], ms);
	free_mat(cmd_lexer);
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