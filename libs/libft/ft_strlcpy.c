/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:09:51 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/12 12:11:47 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	size;

	size = 0;
	while (src[size])
		size++;
	if (len == 0)
		return (size);
	while (*src && --len)
		*dest++ = *src++;
	*dest = 0;
	return (size);
}
