/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:02:31 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/24 13:08:59 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char c, int quotes)
{
	if (c == '\"')
	{
		if (!quotes)
			return (1);
		else if (quotes == 1)
			return (0);
	}
	else if (c == '\'')
	{
		if (!quotes)
			return (2);
		else if (quotes == 2)
			return (0);
	}
	return (quotes);
}

char	*lexer_quotes(char *cmd)
{
	int		i;
	int		quotes;
	char	**ret;

	i = -1;
	quotes = 0;
	while (cmd[++i])
	{
		quotes = check_quotes(cmd[i], quotes);
		if ((cmd[i] == '\'' || cmd[i] == '\"') && !quotes)
			cmd[i] = SEP;
		else if ((cmd[i] == '\'' && quotes == 2) || 
		(cmd[i] == '\"' && quotes == 1))
			cmd[i] = SEP;
	}
	ret = ft_split(cmd, SEP);
	if (!*ret)
	{
		ret = free_mat(ret);
		return (ft_strdup(""));
	}
	return (ft_mattstr_copy(ret));
} 

// char *lexer_quotes(char *cmd, int exit_status)
// {
//     int     i;
//     int     j;
//     int     quotes;
//     char    *result;
//     char    *temp;

//     i = 0;
//     j = 0;
//     quotes = 0;
//     result = (char *)malloc(1024);
//     if (!result)
//         return (NULL);
//     while (cmd[i])
//     {
//         quotes = check_quotes(cmd[i], quotes);
//         if (cmd[i] == '$' && quotes != 2)
//         {
//             temp = expand_variable(&cmd[i], exit_status);
//             while (*temp)
//                 result[j++] = *temp++;
//             while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '?'))
//                 i++;
//             free(temp);
//         }
//         else
//         {
//             result[j++] = cmd[i++];
//         }
//     }
//     result[j] = '\0';
//     return (result);
// }

static char	*filler(char *input, int pos)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_calloc(ft_strlen(input) + 3, sizeof (char));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++j < pos)
		ret[j] = input[++i];
	i++;
	ret[j++] = SEP;
	ret[j++] = input[i++];
	if (input[i] == input[i - 1] && input[i] != '|')
		ret[j++] = input[i++];
	ret[j++] = SEP;
	while (input[i])
		ret[j++] = input[i++];
	ret[j] = '\0';
	input = free_ptr(input);
	return (ret);
}

char	**lexer(char *input)
{
	int		i;
	int		quotes;
	char	*temp;
	char	**ret;

	i = -1;
	quotes = 0;
	temp = ft_strdup(input);
	while (temp && temp[++i])
	{
		if ((temp[i] == '|' || temp[i] == '>' || temp[i] == '<' ) && !quotes)
		{
			temp = filler(temp, i);
			i = i + 2;
		}
		else if (temp[i] == '\"' || temp[i] == '\'')
			quotes = check_quotes(temp[i], quotes);
	}
	if (quotes)
		temp = free_ptr(temp);
	ret = ft_split(temp, SEP);
	temp = free_ptr(temp);
	return (ret);
}
