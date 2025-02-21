/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:42:04 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 04:30:41 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_pwd(t_mini *mini, t_cmd *cmd)
{
	char	*pwd;

	(void)mini;
	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_error("error retrieving current directory", \
		"getcwd", NULL, 1));
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
