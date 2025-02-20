/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:27:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/20 00:54:42 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int check_valide_export(char *str)
{
	int i;

	if (str == NULL || str[0] == '=' || ft_isdigit(str[0]))
	{
		print_export_error(str);
		return (0);
	}
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			print_export_error(str);
			return (0);
		}
		i++;
	}
	return (1);
}
