/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:27:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 02:29:45 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_valide_export(char *str)
{
	int	i;

	if (str == NULL || str[0] == '=' || ft_isdigit(str[0]))
		return (ft_error("export", "not a valid identifier", str, 0));
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ft_error("export", "not a valid identifier", str, 0));
		i++;
	}
	return (0);
}
