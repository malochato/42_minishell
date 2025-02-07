/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_protected.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:04:59 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/28 00:48:41 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_protected(char *s, int *count)
{
	if (s == NULL)
	{
		ft_putstr_protected("(null)", count);
		return ;
	}
	while (*s)
	{
		ft_putchar_count(*s, count);
		s++;
	}
}
