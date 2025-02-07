/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_negatif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:47:23 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/28 00:48:11 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_negatif(int nb, int *count)
{
	unsigned int	nbr;

	if (nb < 0)
	{
		nbr = -nb;
		ft_putchar_count('-', count);
	}
	else
		nbr = nb;
	if (nbr >= 10)
		ft_putnbr_negatif(nbr / 10, count);
	ft_putchar_count(((nbr % 10) + 48), count);
}
