/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:02:31 by dalara-s          #+#    #+#             */
/*   Updated: 2025/03/25 23:09:58 by malde-ch         ###   ########.fr       */
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
		if ((temp[i] == '|' || temp[i] == '>' || temp[i] == '<') && !quotes)
		{
			temp = filler(temp, i);
			i = i + 2;
		}
		else if (temp[i] == '\"' || temp[i] == '\'')
			quotes = check_quotes(temp[i], quotes);
		else if (temp[i] == ' ' && !quotes)
			temp[i] = SEP;
	}
	if (quotes)
		temp = free_ptr(temp);
	ret = ft_split(temp, SEP);
	temp = free_ptr(temp);
	return (ret);
}
