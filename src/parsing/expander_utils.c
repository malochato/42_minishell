/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalara-s <dalara-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/04/01 15:53:47 by dalara-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_expand	init_expansion(t_mini *ms, char *cmd, char **envp, t_expand exp)
{
	while (cmd[++exp.end])
	{
		exp.quotes = check_quotes(cmd[exp.end], exp.quotes);
		if (cmd[exp.end] == '$' && exp.quotes != 2)
		{
			exp.hold_str[exp.ex++] = ft_substr(cmd, exp.start, exp.end - \
			exp.start);
			exp.start = exp.end;
		}
		else if (cmd[exp.start] == '$' && cmd[exp.end] != '{' && \
		!ft_isalnum(cmd[exp.end]) && cmd[exp.end] != '?' \
		&& cmd[exp.end] != '_')
		{
			exp.hold_str[exp.ex++] = get_envp(ms, ft_substr(cmd, exp.start, \
			exp.end - exp.start), envp);
			if (cmd[exp.end] == '}' && cmd[exp.start + 1] == '{' \
			&& cmd[exp.end + 1])
				exp.end++;
			exp.start = exp.end;
		}
	}
	return (exp);
}

char	*expand(t_mini *ms, char *cmd, char **envp)
{
	t_expand	exp;

	ft_bzero (&exp, sizeof(t_expand));
	while (cmd[exp.i])
		exp.ex_n += (cmd[exp.i++] == '$');
	exp.ex = (exp.ex_n * 2) + 2;
	exp.hold_str = ft_calloc(exp.ex, sizeof(char *));
	if (!exp.hold_str)
		return (NULL);
	exp.ex = 0;
	exp.end = -1;
	exp = init_expansion (ms, cmd, envp, exp);
	if (cmd[exp.start] == '$')
		exp.hold_str[exp.ex++] = get_envp(ms, ft_substr(cmd, exp.start, \
		exp.end - exp.start), envp);
	else
		exp.hold_str[exp.ex++] = ft_substr(cmd, exp.start, exp.end - exp.start);
	return (ft_mattstr_copy(exp.hold_str));
}

static char	*exit_status(t_mini *ms, char *f, char *cmd)
{
	char	*ret;
	char	*res;
	char	*temp;

	ret = NULL;
	if (!*cmd)
	{
		f = free_ptr(f);
		return (ft_strdup("$"));
	}
	if (cmd && cmd[0])
		ret = ft_strdup(++cmd);
	f = free_ptr(f);
	temp = ft_itoa(ms->exit_status);
	res = ft_strjoin(temp, ret);
	free(ret);
	free(temp);
	return (res);
}

int	find_equalsing(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*get_envp(t_mini *ms, char *cmd, char **envp)
{
	char	*ret;
	int		len;
	int		var_len;

	ret = cmd;
	cmd++;
	if (*cmd == '{')
		len = ft_strlen(++cmd);
	else
		len = ft_strlen(cmd);
	if (*cmd == '?' || len == 0)
		return (exit_status(ms, ret, cmd));
	while (*envp)
	{
		var_len = find_equalsing(*envp);
		if (!ft_strncmp(cmd, *envp, var_len) && \
			!ft_strncmp(cmd, *envp, var_len))
		{
			ret = free_ptr(ret);
			return (ft_strdup(*envp + len + 1));
		}
		envp++;
	}
	ret = free_ptr(ret);
	return (ft_strdup(""));
}
