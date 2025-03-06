/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:53:33 by malde-ch          #+#    #+#             */
/*   Updated: 2025/03/06 23:03:06 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


#include <signal.h>
#include <termios.h>
#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"


void false_parser1(t_mini *mini)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	t_cmd *cmd4 = malloc(sizeof(t_cmd));
	t_cmd *cmd5 = malloc(sizeof(t_cmd));

	if (!cmd1 || !cmd2 || !cmd3 || !cmd4 || !cmd5)
	{
		perror("malloc");
		exit(1);
	}

	cmd1->cmd = ft_split("ls", ' ');
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;
	cmd1->operator = OP_NONE;
	cmd1->next = cmd2;

	cmd2->cmd = ft_split(">", ' ');
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->operator = OP_REDIRECT_OUT;
	cmd2->next = cmd3;

	cmd3->cmd = ft_split("fichier1", ' ');
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->operator = OP_NONE;
	cmd3->next = cmd4;

	cmd4->cmd = ft_split(">", ' ');
	cmd4->fd_in = -1;
	cmd4->fd_out = -1;
	cmd4->operator = OP_REDIRECT_OUT;
	cmd4->next = cmd5;

	cmd5->cmd = ft_split("fichier7", ' ');
	cmd5->fd_in = -1;
	cmd5->fd_out = -1;
	cmd5->operator = OP_NONE;
	cmd5->next = NULL;

	mini->cmd = cmd1;
}

void false_parser2(t_mini *mini)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	t_cmd *cmd4 = malloc(sizeof(t_cmd));
	t_cmd *cmd5 = malloc(sizeof(t_cmd));

	if (!cmd1 || !cmd2 || !cmd3 || !cmd4 || !cmd5)
	{
		perror("malloc");
		exit(1);
	}

	cmd1->cmd = ft_split("grep ola", ' ');
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;
	cmd1->operator = OP_NONE;
	cmd1->next = cmd2;

	cmd2->cmd = ft_split(">>", ' ');
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->operator = OP_REDIRECT_OUT_APPEND;
	cmd2->next = cmd3;

	cmd3->cmd = ft_split("fichier1", ' ');
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->operator = OP_NONE;
	cmd3->next = cmd4;

	cmd4->cmd = ft_split("<<", ' ');
	cmd4->fd_in = -1;
	cmd4->fd_out = -1;
	cmd4->operator = OP_HERE_DOC;
	cmd4->next = cmd5;

	cmd5->cmd = ft_split("EOF", ' ');
	cmd5->fd_in = -1;
	cmd5->fd_out = -1;
	cmd5->operator = OP_NONE;
	cmd5->next = NULL;

	mini->cmd = cmd1;
}

void false_parser3(t_mini *mini)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	t_cmd *cmd4 = malloc(sizeof(t_cmd));
	t_cmd *cmd5 = malloc(sizeof(t_cmd));

	if (!cmd1 || !cmd2 || !cmd3 || !cmd4)
	// || !cmd5)
	{
		perror("malloc");
		exit(1);
	}

	cmd1->cmd = ft_split("grep 7", ' ');
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;
	cmd1->operator = OP_NONE;
	cmd1->next = cmd2;

	cmd2->cmd = ft_split("<", ' ');
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->operator = OP_REDIRECT_IN;
	cmd2->next = cmd3;

	cmd3->cmd = ft_split("fichier7", ' ');
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->operator = OP_NONE;
	cmd3->next = cmd4;

	cmd4->cmd = ft_split(">>", ' ');
	cmd4->fd_in = -1;
	cmd4->fd_out = -1;
	cmd4->operator = OP_REDIRECT_OUT_APPEND;
	cmd4->next = cmd5;

 	cmd5->cmd = ft_split("<<", ' ');
	cmd5->fd_in = -1;
	cmd5->fd_out = -1;
	cmd5->operator = OP_HERE_DOC;
	cmd5->next = NULL;

	mini->cmd = cmd1;
}

void false_parser4(t_mini *mini)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	t_cmd *cmd3 = malloc(sizeof(t_cmd));


	if (!cmd1 || !cmd2 || !cmd3 )
	{
		perror("malloc");
		exit(1);
	}

	cmd1->cmd = ft_split("ls -l", ' ');
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;
	cmd1->operator = OP_NONE;
	cmd1->next = cmd2;

	cmd2->cmd = ft_split("|", ' ');
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->operator = OP_PIPE;
	cmd2->next = NULL;

/* 	cmd3->cmd = ft_split("grep 7", ' ');
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->operator = OP_NONE;
	cmd3->next = NULL; */

	mini->cmd = cmd1;
}

void false_parser5(t_mini *mini)
{
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	t_cmd *cmd4 = malloc(sizeof(t_cmd));
	t_cmd *cmd5 = malloc(sizeof(t_cmd));


	if (!cmd1 || !cmd2 || !cmd3 || !cmd4 || !cmd5)
	{
		perror("malloc");
		exit(1);
	}

	cmd1->cmd = ft_split("ls", ' ');
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;
	cmd1->operator = OP_NONE;
	cmd1->next = cmd2;

	cmd2->cmd = ft_split(">", ' ');
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->operator = OP_REDIRECT_OUT;
	cmd2->next = cmd3;

	cmd3->cmd = ft_split("fichiers22", ' ');
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->operator = OP_NONE;
	cmd3->next = cmd4;

	cmd4->cmd = ft_split("mini", ' ');
	cmd4->fd_in = -1;
	cmd4->fd_out = -1;
	cmd4->operator = OP_NONE;
	cmd4->next = cmd5;

	cmd5->cmd = ft_split("777", ' ');
	cmd5->fd_in = -1;
	cmd5->fd_out = -1;
	cmd5->operator = OP_NONE;
	cmd5->next = NULL;

	mini->cmd = cmd1;
}

void	parse_input_simple(t_mini *mini, char *input)
{
	mini->cmd = malloc(sizeof(t_cmd));
	if (mini->cmd == NULL)
	{
		perror("malloc");
		free_all(mini);
		exit(1);
	}
	mini->cmd->cmd = ft_split(input, ' ');
	if (mini->cmd->cmd == NULL)
	{
		mini->cmd->cmd = malloc(sizeof(char *));
		if (mini->cmd->cmd == NULL)
			ft_exit(mini, 1, "malloc");
		mini->cmd->cmd[0] = NULL;
	}
	mini->cmd->fd_in = -1;
	mini->cmd->fd_out = -1;
	mini->cmd->operator = OP_NONE;
	mini->cmd->next = NULL;
}


int	shell_init(t_mini *mini)
{
	char	*pwd;
	char	*char_shlvl;
	int		shlvl;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_error("error retrieving current directory", "getcwd", \
		NULL, 1));
	env_manager(mini, ft_strdup("PWD"), pwd);
	char_shlvl = get_env_value(mini->env, "SHLVL");
	if (char_shlvl != NULL)
	{
		shlvl = ft_atoi(char_shlvl);
		if (shlvl >= 0)
			char_shlvl = ft_itoa(shlvl + 1);
		else
			char_shlvl = ft_strdup("1");
	}
	else
		char_shlvl = ft_strdup("1");
	env_manager(mini, ft_strdup("SHLVL"), char_shlvl);
	return (0);
}

// Désactiver l'écho du signal SIGQUIT
void disable_sigquit_echo()
{
	struct termios term;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	term.c_lflag &= ~ECHOCTL; // Désactiver l'écho des caractères de contrôle
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}



void handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("Received SIGINT (Ctrl+C), exiting...\n");
		exit(0);
	}
}


char *get_prompt(t_mini *mini)
{
		char	*prompt;
		char	*exit_status_str;
		char	*pwd;
		char	*home;
		char	*home_replacement;
		char	*color;


		pwd = getcwd(NULL, 0);
		home = get_env_value(mini->env, "HOME");
		if (home != NULL && pwd != NULL && ft_strncmp(pwd, home, ft_strlen(home)) == 0)
		{
			home_replacement = ft_strjoin("~", pwd + ft_strlen(home));
			free(pwd);
			pwd = home_replacement;
		}
		exit_status_str = ft_itoa(mini->exit_status);
		if (mini->exit_status == 0)
			color = COLOR_GREEN;
		else
			color = COLOR_RED;

		size_t prompt_size = ft_strlen("minishell: ") + ft_strlen(pwd) + ft_strlen(" [") +
						 ft_strlen(color) + ft_strlen(exit_status_str) +
						 ft_strlen(COLOR_RESET) + ft_strlen("] % ") + 1;

		prompt = malloc(prompt_size);		
		if (prompt == NULL)
			ft_exit(mini, 1, "ERROR malloc");
		
		ft_strlcpy(prompt, "minishell: ", prompt_size);
		if (pwd != NULL)
		{
			ft_strlcat(prompt, pwd, prompt_size);
		}
		ft_strlcat(prompt, " [", prompt_size);
		ft_strlcat(prompt, color, prompt_size);
		ft_strlcat(prompt, exit_status_str, prompt_size);
		ft_strlcat(prompt, COLOR_RESET, prompt_size);
		ft_strlcat(prompt, "] % ", prompt_size);

		free(exit_status_str);
		free(pwd);
		return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*input;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_mini));
	if (mini == NULL)
	{
		ft_exit(mini, 1, "ERROR malloc");
	}
	mini->cmd = NULL;
	mini->exit_status = 0;
	mini->env = parser_env(envp);
	
	if (!mini->env)
	{
		ft_exit(mini, 1, "ERROR malloc");
	}

	mini->envp = duplicate_env(envp);
	shell_init(mini);


	disable_sigquit_echo();
	if (signal(SIGINT, handle_signal) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
	if (signal(SIGQUIT, handle_signal) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}


	while (1)
	{
		char *prompt = get_prompt(mini);
		input = readline(prompt);
		free(prompt);
		if (input == NULL)
			break ;
		if (*input)
		{
			add_history(input);
		}
		
		if (ft_strncmp(input, "aa", 2) == 0)
		{
			false_parser1(mini);
		}
		else if (ft_strncmp(input, "ss", 2) == 0)
		{
			false_parser2(mini);
		}
		else if (ft_strncmp(input, "dd", 2) == 0)
		{
			false_parser3(mini);
		}
		else if (ft_strncmp(input, "ff", 2) == 0)
		{
			false_parser4(mini);
		}
		else if (ft_strncmp(input, "gg", 2) == 0)
		{
			false_parser5(mini);
		}
		else
		{
			parse_input_simple(mini, input);
		}
		exec(mini);
		//printf("You entered: %s\n", input);
		free(input);
		free_cmd(mini->cmd);
		mini->cmd = NULL;
	}
	rl_clear_history();
	free_all(mini);
	return (0);
}
