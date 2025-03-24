/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:02:14 by dalara-s          #+#    #+#             */
/*   Updated: 2025/02/11 17:23:36 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_mattstr_copy(char **mat)
{
	char	*str;
	char	*temp;
	int		i;

	str = ft_strdup(mat[0]);
	i = 0;
	while (mat[++i])
	{
		temp = str;
		str = ft_strjoin(temp, mat[i]);
		temp = free_ptr(temp);
	}
	mat = free_mat(mat);
	return (str);
}

char	**ft_matdup(char **mat)
{
	char	**temp;
	size_t	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat[i])
		i++;
	temp = ft_calloc (i + 1, sizeof (char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		temp[i] = ft_strdup (mat[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

char	**split_args(char *input)
{
	int		i;
	int		quotes;
	char	**ret;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == ' ' && !quotes)
			input[i] = SEP;
		else if (input[i] == '\"' || input[i] == '\'')
			quotes = check_quotes(input[i], quotes);
	}
	ret = ft_split(input, SEP);
	return (ret);
}

char	**token_to_mat(t_token *token)
{
	int		i;
	int		j;
	char	**ret;
	t_token	*temp;

	temp = token;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	ret = ft_calloc((i + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		ret[j] = ft_strdup(token->cmd);
		token = token->next;
	}
	ret[j] = NULL;
	return (ret);
}
