/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:09:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 16:10:53 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**copy_array(char **array, int size)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (size + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(array[i]);
		if (copy[i] == NULL)
		{
			while (i >= 0)
			{
				free(copy[i]);
				i--;
			}
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[size] = NULL;
	return (copy);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	array_size(char **array)
{
	int	size;

	size = 0;
	while (array[size] != NULL)
		size++;
	return (size);
}
