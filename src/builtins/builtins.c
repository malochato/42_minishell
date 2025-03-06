/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:56:50 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/04 04:47:19 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	init_builtins(t_builtin *builtins)
{
	builtins[0].name = "pwd";
	builtins[0].func = builtin_pwd;
	builtins[1].name = "export";
	builtins[1].func = builtin_export;
	builtins[2].name = "env";
	builtins[2].func = builtin_env;
	builtins[3].name = "echo";
	builtins[3].func = builtin_echo;
	builtins[4].name = "unset";
	builtins[4].func = builtin_unset;
	builtins[5].name = "cd";
	builtins[5].func = builtin_cd;
	builtins[6].name = "exit";
	builtins[6].func = builtin_exit;
	builtins[7].name = NULL;
	builtins[7].func = NULL;
}

t_builtin_func	get_builtin_func(const char *name, t_builtin *builtins)
{
	int	i;

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(name, builtins[i].name, ft_strlen(name)) == 0 \
			&& ft_strlen(name) == ft_strlen(builtins[i].name))
			return (builtins[i].func);
		i++;
	}
	return (NULL);
}
