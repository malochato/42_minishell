
#include "minishell.h"

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

	cmd1->cmd = ft_split("echo ", ' ');
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
	cmd1->cmd = ft_split("ls", ' ');
	cmd1->fd_in = -1;
	cmd1->fd_out = -1;
	cmd1->operator = OP_NONE;
	cmd1->next = cmd2;

	cmd2->cmd = ft_split("|", ' ');
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->operator = OP_PIPE;
	cmd2->next = cmd3;

	cmd3->cmd = ft_split("grep m", ' ');
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->operator = OP_NONE;
	cmd3->next = NULL;

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
