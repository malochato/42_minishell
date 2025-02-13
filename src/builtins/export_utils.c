/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:27:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 18:04:04 by malde-ch         ###   ########.fr       */
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

void print_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}


static	int is_valid_identifier(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int check_valide_export(char *str)
{
	char	**tmp;

	if (str == NULL || ft_isdigit(str[0]))
		return (1);
	tmp = ft_split(str, '=');
	if (tmp == NULL)
	{
		perror("Error with malloc");
		return (1);
	}
	if (tmp[0] == NULL || !is_valid_identifier(tmp[0]) || str[0] == '=')
	{
		print_export_error(str);
		free_split(tmp);
		return (1);
	}
	free_split(tmp);
	return (0);
}


