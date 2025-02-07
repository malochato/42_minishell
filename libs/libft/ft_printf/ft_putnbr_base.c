/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:15:54 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/28 00:49:24 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr_base(unsigned long nbr, char *base, int *count)
{
	unsigned int	len;
	unsigned long	nb;

	len = ft_strlen(base);
	nb = nbr;
	if (nb < len)
		ft_putchar_count(base[nb], count);
	if (nb >= len)
	{
		ft_putnbr_base(nb / len, base, count);
		ft_putnbr_base(nb % len, base, count);
	}
}
