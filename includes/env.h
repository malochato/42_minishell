/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:33:05 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/19 21:33:58 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

int	env_manager(t_mini *mini, char *key, char *value);



// UTILS
void update_env_array(t_mini *mini);
int		ft_lstsize_env(t_env_var *env);
int add_env_var(t_mini *mini, char *key, char *value);
int update_env_var(t_env_var *env, char *key, char *value);


#endif