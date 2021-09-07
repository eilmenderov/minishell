#include "head_minishell.h"

void	ft_child(t_cmd *cmd)
{
	return ;
}

static void	ft_print_fd(t_data *data)
{
	int	i;

	i = 0;
	while (data->fd_pipes[i])
	{
		printf("fd[%d][0] = %d\tfd[%d][1] = %d\n", i,
			data->fd_pipes[i][0], i, data->fd_pipes[i][1]);
		i++;
	}
	printf("OK\n");
}

void	ft_multiple_cmd(t_cmd *cmd)
{
	int		pid;
	t_cmd	*tmp;

	ft_create_pipes(cmd->data);
	tmp = cmd;
	while (tmp)
	{
		if (tmp->delim != PIPE && tmp->delim != 0)
			ft_pr_error("Sorry not supported yeat", -1, 0, 0);
		pid = fork();
		if (pid < 0)
			ft_pr_error(ERR_FORK, -1, 0, 0);
		else if (!pid)
		{
			printf("cmd - %d\n", tmp->num_start + 1);
			ft_close_pipes(tmp->data, tmp, tmp->num_start);
			ft_print_fd(cmd->data);
			ft_child(tmp), exit(1);
		}
		tmp = tmp->next;
	}
	ft_close_pipes(cmd->data, cmd, -1);
	ft_wait_all_cmd(cmd->data);
	return ;
}
