#include"minishell.h"

void name_generator(char **filename)
{
	int fd;
	int rand;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &rand, sizeof(rand));
	if (rand < 0)
		rand *= -1;
	rand = rand/1000000;
	*filename=ft_strjoin("/tmp/tmp", ft_itoa(rand));
}

void open_heredoc_file(char *delimiter, char **filename)
{
	int temp;
	char *rl;

	name_generator(filename);
	temp = open(*filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while(1)
	{
		rl = readline(">");
		if (!(ft_strcmp(rl, delimiter)))
			break ;
		ft_putendl_fd(rl, temp);
	}
	close(temp);
}

void unlink_heredocs()
{
	t_parse *cmd_list;
	t_redirection *redr;

	cmd_list = mini.command;
	while(cmd_list)
	{
		redr = cmd_list->redirection;
		while(redr)
		{
			if (redr->type == HEREDOC_REDR)
				unlink(redr->file);
			redr = redr->next;
		}
		cmd_list = cmd_list->next;
	}
}

void implement_heredoc()
{
	t_parse *cmd_list;
	t_redirection *redr;
	char *filename = NULL;

	cmd_list = mini.command;
	while (cmd_list)
	{
		redr = cmd_list->redirection;
		while(redr)
		{
			if (redr->type == HEREDOC_REDR)
			{
				open_heredoc_file(redr->file, &filename);
				redr->file = ft_strdup(filename);
			}
			redr = redr->next;
		}
		cmd_list = cmd_list->next;
	}
}