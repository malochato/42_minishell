/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/17 11:14:37 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{

	t_mini	mini;
	(void)envp;
	(void)argc;
	(void)argv;
	
	char *input;
	mini.cmd = malloc(sizeof(t_cmd));
	if (mini.cmd == NULL) {
        perror("malloc");
        return 1;
    }
	mini.env = NULL;
	while (1) {
        input = readline("minishell $>");
		// this as to change (it's need to not be static),we have to put minishell + the directory where we are in.
        if (input == NULL)
            break;
		// this is CRL + D
        if (*input) {
            add_history(input);
			// this is to add the input in the history	
			// and use it with the up arrow	
        }

        printf("You entered: %s\n", input);
		if (mini.env != NULL)
		{
			free_env(mini.env);
		}
		mini.env = parser_env(envp);
    }
	rl_clear_history();
	free(mini.cmd->cmd);
	// this is to clear the history
	// we need it also for the exit() fnction that will be doing.
    return 0;
}
