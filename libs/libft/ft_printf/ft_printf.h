/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:41:05 by malde-ch          #+#    #+#             */
/*   Updated: 2024/09/28 00:45:38 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

void	ft_putchar_count(char c, int *count);
void	ft_putnbr_negatif(int nb, int *count);
void	ft_putstr_protected(char *s, int *count);
void	ft_putnbr_base(unsigned long nbr, char *base, int *count);
int		ft_printf(const char *s, ...);
void	ft_conversions(int *count, char c, va_list args);

#endif 
