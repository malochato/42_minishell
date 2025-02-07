/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:08:06 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/16 11:41:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*tdest;
	const unsigned char	*tsrc;

	tdest = (unsigned char *)dest;
	tsrc = (const unsigned char *)src;
	if (tdest < tsrc)
	{
		while (len--)
			*tdest++ = *tsrc++;
	}
	else
	{
		tdest += len;
		tsrc += len;
		while (len--)
			*(--tdest) = *(--tsrc);
	}
	return (dest);
}
