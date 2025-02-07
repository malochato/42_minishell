/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:44:40 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/02 18:44:06 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_ptr(int *count, va_list args)
{
	unsigned long	ptr;

	ptr = va_arg(args, unsigned long);
	if (!ptr)
		ft_putstr_protected("(nil)", count);
	else
	{
		ft_putstr_protected("0x", count);
		ft_putnbr_base(ptr, "0123456789abcdef", count);
	}
}

void	ft_conversions(int *count, char c, va_list args)
{
	if (c == 'd' || c == 'i')
		ft_putnbr_negatif(va_arg(args, int), count);
	else if (c == 'c')
		ft_putchar_count(va_arg(args, int), count);
	else if (c == 's')
		ft_putstr_protected(va_arg(args, char *), count);
	else if (c == '%')
		ft_putchar_count('%', count);
	else if (c == 'u')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789", count);
	else if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", count);
	else if (c == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", count);
	else if (c == 'p')
		ft_ptr(count, args);
	else
	{
		ft_putchar_count('%', count);
		ft_putchar_count(c, count);
	}
}
