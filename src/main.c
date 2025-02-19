/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/18 15:34:25 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **duplicate_env(char **envp)
{
	int i;
	char **new_env;

	for (i = 0; envp[i] != NULL; i++)
		;
	new_env = malloc((i + 1) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	for (i = 0; envp[i] != NULL; i++)
	{
		new_env[i] = strdup(envp[i]);
		if (new_env[i] == NULL)
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
	}
	new_env[i] = NULL;
	return (new_env);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char	*input;

	(void)argc;
	(void)argv;
	mini.cmd = malloc(sizeof(t_cmd));
	mini.cmd->cmd = malloc(sizeof(char *));
	mini.cmd->cmd[0] = NULL;
	if (mini.cmd == NULL)
	{
		perror("malloc");
		return (1);
	}
	mini.env = parser_env(envp);
	mini.envp = duplicate_env(envp);

	while (1)
	{
		input = readline("minishell $>");
		// this as to change (it's need to not be static),we have to put minishell + the directory where we are in.
		if (input == NULL)
			break ;
		// this is CRL + D
		if (*input)
		{
			add_history(input);
			// this is to add the input in the history	
			// and use it with the up arrow	
		}

		        // Libérer la mémoire de la commande précédente
        if (mini.cmd->cmd != NULL) {
            for (int i = 0; mini.cmd->cmd[i] != NULL; i++) {
                free(mini.cmd->cmd[i]);
            }
            free(mini.cmd->cmd);
        }


        // Allouer et initialiser la nouvelle commande
        mini.cmd->cmd = ft_split(input, ' ');
		if (mini.cmd->cmd == NULL){
			mini.cmd->cmd = malloc(sizeof(char *));
		}
	        mini.cmd->next = NULL;

        exec(&mini);

		printf("You entered: %s\n", input);
		free(input);
	}
	rl_clear_history();
	if(mini.cmd->cmd != NULL)
	{
		int i = 0;
		while(mini.cmd->cmd[i] != NULL)
		{
			free(mini.cmd->cmd[i]);
			i++;
		}
		free(mini.cmd->cmd);
	}

	if (mini.cmd != NULL)
		free(mini.cmd);
	// need real free function
	if (mini.env != NULL)
		free_env(mini.env);
	if (mini.envp != NULL)
	{
		for (int i = 0; mini.envp[i] != NULL; i++)
			free(mini.envp[i]);
		free(mini.envp);
	}
	return (0);
}