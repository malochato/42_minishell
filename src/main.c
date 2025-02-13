/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/02/13 11:59:48 by malde-ch         ###   ########.fr       */
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
    mini.cmd->cmd = NULL;
    while (1) {
        input = readline("minishell $>");
        if (input == NULL)
            break;
        if (*input) {
            add_history(input);
        }

        // Libérer la mémoire de la commande précédente
        if (mini.cmd->cmd != NULL) {
            for (int i = 0; mini.cmd->cmd[i] != NULL; i++) {
                free(mini.cmd->cmd[i]);
            }
            free(mini.cmd->cmd);
        }

        // Allouer et initialiser la nouvelle commande
        mini.cmd->cmd = ft_split("export", ' ');
	        mini.cmd->next = NULL;
        mini.envp = envp;

        exec(&mini);

        // Libérer la mémoire de l'input après utilisation
        free(input);
    }

    rl_clear_history();
    if (mini.cmd->cmd != NULL) {
        for (int i = 0; mini.cmd->cmd[i] != NULL; i++) {
            free(mini.cmd->cmd[i]);
        }
        free(mini.cmd->cmd);
    }
    free(mini.cmd);
    return 0;
}