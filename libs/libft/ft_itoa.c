/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:16:24 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/16 20:27:22 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*result;
	int				len;
	unsigned int	nb;

	len = num_len(n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = 0;
	if (n == 0)
		*result = '0';
	if (n < 0)
		nb = (unsigned int)(-n);
	else
		nb = (unsigned int)n;
	while (nb)
	{
		result[--len] = nb % 10 + 48;
		nb /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

// Here the Norme is rather bad, 
// it makes me do things that reduce the speed 
// and quality of my code.
