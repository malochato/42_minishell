/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:07:51 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 13:57:03 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


static	int is_option_n(char *str)
{
	int i;

	i = 0;
	if 	(str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int    builtin_echo(t_mini *mini)
{
	int i;
	int n_option;

	i = 1;
	n_option = 0;
	if (mini->cmd->cmd[i] != NULL && is_option_n(mini->cmd->cmd[i]) )
	{
		n_option = 1;
		i++;
	}
	while (mini->cmd->cmd[i] != NULL)
	{
		printf("%s", mini->cmd->cmd[i]);
		if (mini->cmd->cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_option == 0)
		printf("\n");
	return (0);
}