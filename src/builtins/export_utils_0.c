/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:27:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 20:01:54 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static	int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_valide_export(char *str)
{
	char	**tmp;
	int		return_value;

	return_value = 0;
	if (str == NULL || ft_isdigit(str[0]))
		return (1);
	tmp = ft_split(str, '=');
	if (tmp == NULL)
	{
		perror("Error with malloc");
		return (2);
	}
	if (tmp[0] == NULL || !is_valid_identifier(tmp[0]) || str[0] == '=')
	{
		print_export_error(str);
		return_value = 1;
	}
	free_split(tmp);
	return (return_value);
}
