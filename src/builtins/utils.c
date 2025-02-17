/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:09:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/17 16:15:24 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_lstsize_env(t_env_var *env)
{
	int			i;
	t_env_var	*tmp;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}


void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}