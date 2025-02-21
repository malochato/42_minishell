/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:45:16 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/21 02:21:49 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_exit(t_mini *mini, int num, char *str)
{
	if (str)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	free_all(mini);
	exit(num);
}

int	is_within_int_range(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && - num < INT_MIN))
			return (0);
		i++;
	}
	return (1);
}

void	check_if_argument_is_num(t_mini *mini)
{
	int		i;
	char	*str;

	str = mini->cmd->cmd[1];
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
		{
			ft_error("exit", "numeric argument required", str, 0);
			ft_exit(mini, 2, NULL);
		}
	}
	if (!is_within_int_range(str))
	{
		ft_error("exit", "numeric argument required", str, 0);
		ft_exit(mini, 2, NULL);
	}
}

int	builtin_exit(t_mini *mini)
{
	ft_putstr_fd("exit\n", 2);
	if (mini->cmd->cmd[1] == NULL)
		ft_exit(mini, mini->exit_status, NULL);
	else if (mini->cmd->cmd[1] != NULL)
		check_if_argument_is_num(mini);
	if (mini->cmd->cmd[2] != NULL)
		return (ft_error("exit", "too many arguments", NULL, 0));
	else
		ft_exit(mini, ft_atoi(mini->cmd->cmd[1]) % 256, NULL);
	return (42);
}
