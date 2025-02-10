/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/07 16:55:20 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char *input;
	while (1) {
        input = readline("minishell >>");
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
        free(input);
    }
	rl_clear_history();
	// this is to clear the history
	// we need it also for the exit() fnction that will be doing.
    return 0;
}
