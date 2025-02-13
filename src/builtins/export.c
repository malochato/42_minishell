/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:49 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 16:10:59 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	selection_sort(char **array, int size)
{
	int		i;
	int		j;
	char	*temp;
	int		indice_min;

	i = 0;
	while (i < size -1)
	{
		indice_min = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(array[j], array[indice_min], \
			ft_strlen(array[j])) < 0)
				indice_min = j;
			j++;
		}
		if (indice_min != i)
		{
			temp = array[i];
			array[i] = array[indice_min];
			array[indice_min] = temp;
		}
		i++;
	}
}

int	handle_export_no_args(t_mini *mini)
{
	int		i;
	int		size;
	char	**tmp;

	size = array_size(mini->envp);
	tmp = copy_array(mini->envp, size);
	if (tmp == NULL)
	{
		perror("Error with malloc");
		return (1);
	}
	selection_sort(tmp, size);
	i = 0;
	while (tmp[i] != NULL)
	{
		printf("declare -x %s\n", tmp[i]);
		i++;
	}
	free_array(tmp);
	tmp = NULL;
	return (0);
}

int	builtin_export(t_mini *mini)
{
	//si export est le seul token
	if (mini->cmd->cmd[1] == NULL)
	{
		// return (handle_export_no_args(mini));
		handle_export_no_args(mini);
	}
	return (0);
}
