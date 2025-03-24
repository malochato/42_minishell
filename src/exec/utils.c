/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:09:25 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/24 17:48:39 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	size_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	append_to_array(t_mini *mini, char ***array, const char *str)
{
	int		size;
	char	**new_array;
	int		i;

	i = 0;
	size = size_array(*array);
	new_array = malloc((size + 2) * sizeof(char *));
	if (new_array == NULL)
		ft_exit(mini, 1, "Error malloc");
	while (i < size)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[size] = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (new_array[size] == NULL)
		ft_exit(mini, 1, "Error malloc");
	ft_strlcpy(new_array[size], str, ft_strlen(str) + 1);
	new_array[size + 1] = NULL;
	free(*array);
	*array = new_array;
}
