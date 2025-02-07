/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:29:48 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/02 18:44:31 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		count;
	va_list	args;

	va_start(args, s);
	count = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == 37)
		{
			ft_conversions(&count, *(s + 1), args);
			s++;
		}
		else
			ft_putchar_count(*s, &count);
		s++;
	}
	va_end(args);
	return (count);
}
