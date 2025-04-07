/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:22 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 16:39:23 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>

# include "types.h"

# include "parsing.h"
# include "exec.h"
# include "builtins.h"
# include "env.h"

# include <signal.h>
# include <termios.h>

# define COLOR_RESET "\033[0m"
# define COLOR_GREEN "\033[32m"
# define COLOR_RED "\033[31m"

// to put in the parsing.h
t_env_var	*parser_env(char **env);
char		**duplicate_env(char **envp);

// From free_all.c
void		free_env(t_env_var *env_var);
void		free_split(char **split);
void		free_cmd(t_cmd *cmd);
void		free_all(t_mini *mini);

// From main.c
void		ft_exit(t_mini *mini, int num, char *str);
void		setup_signals(void);
void		handle_sigint(int signal);

// From main_utils.c
int			update_exit_status(int value);
void		handle_signal(int signal);
void		signal_handler(void);
int			init_shell_env(t_mini *mini);

// From prompt_utils.c
char		*get_prompt(void);

#endif
