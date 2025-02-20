/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:04 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 23:04:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_pwd(t_mini *mini)
{
	char	*pwd;

	(void)mini;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (3);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
