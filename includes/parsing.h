/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:37:12 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/07 16:39:48 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# ifndef SEP
#  define SEP -1
# endif

int			expander(t_mini *ms, t_token **head);

char		*get_envp(t_mini *ms, char *cmd, char **envp);
void		insert_token(t_token **head, char *token);
t_env_var	*parser_env(char **env);
void		free_env(t_env_var *env_var);
char		*free_ptr(char *ptr);
char		**lexer(char *input);
int			parser(t_mini *ms, char *str);
int			check_quotes(char c, int quotes);
char		**free_mat(char **mat);

t_token		*free_token(t_token *token);

char		*expand(t_mini *ms, char *cmd, char **envp);
void		fill_token(t_token **head, char **cmd_lexer);

char		*ft_mattstr_copy(char **mat);
char		**split_args(char *input);
void		create_cmd_list(t_mini *ms);

char		**token_to_mat(t_token *token);
int			syntax_checker(t_mini *ms);
//void expand_tokens(t_token *head, int exit_status);
//char *expand_variable(char *input, int exit_status);

void		free_all_parsing(t_mini *ms);
t_cmd		*free_cmd_parsing(t_cmd *cmd);

#endif