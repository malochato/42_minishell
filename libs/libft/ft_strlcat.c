/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:16:15 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/23 19:42:40 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	i;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	len_dest = ft_strlen(dst);
	i = 0;
	while (src[i] && len_dest + 1 < size)
	{
		dst[len_dest] = src[i];
		len_dest++;
		i++;
	}
	dst[len_dest] = 0;
	return (len_dest + ft_strlen(&src[i]));
}
