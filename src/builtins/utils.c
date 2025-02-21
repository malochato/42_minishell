/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:09:32 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 05:08:03 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
4. Messages d’erreurs standardisés POSIX

Les messages d’erreurs doivent suivre une structure simple :

    Nom de la commande : Suivi d’un : pour identifier la source de l’erreur.
    Type d’erreur : Une description concise de l’erreur rencontrée.
    Nom problématique (facultatif) : Affiché si l’erreur est liée à un argument.

*/
int	ft_error(char *cmd, char *error_type, char *val, int perror_active )
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (val != NULL)
	{
		ft_putstr_fd(val, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_type, 2);
	if (perror_active)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
		ft_putstr_fd("\n", 2);
	return (1);
}
