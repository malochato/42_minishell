/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:10:27 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/20 16:33:36 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_string(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		if (*str)
			count++;
		while (*str && !(*str == c))
			str++;
	}
	return (count);
}

static char	**free_strings(char **strings, int i)
{
	while (i > 0)
		free(strings[--i]);
	free(strings);
	return (NULL);
}

static char	**split_words(const char *str, char c, char **strings)
{
	int			i;
	const char	*end;

	i = 0;
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		if (!*str)
			break ;
		end = ft_strchr(str, c);
		if (!end)
			end = str + ft_strlen(str);
		strings[i] = ft_substr(str, 0, end - str);
		if (!strings[i])
			return (free_strings(strings, i));
		i++;
		str = end;
	}
	strings[i] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)malloc((count_string(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	strings = split_words(s, c, strings);
	return (strings);
}
