/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:54:15 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/20 16:38:41 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	while (is_set(set, s1[start]) && s1[start])
		start++;
	while (is_set(set, s1[len - 1]) && (len - 1))
		len--;
	return (ft_substr(s1, start, (len - start)));
}
