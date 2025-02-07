/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:34:00 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/11 18:10:23 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char		*tdest;
	const unsigned char	*tsrc;

	tdest = dest;
	tsrc = src;
	while (len--)
		*tdest++ = *tsrc++;
	return (dest);
}
