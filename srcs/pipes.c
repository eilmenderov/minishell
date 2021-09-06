#include "head_minishell.h"

void	ft_create_pipes(t_data *data)
{
	int	i;

	data->fd_pipes = malloc(sizeof(int *) * (data->total_cmd + 1));
	i = 0;
	while (i < data->total_cmd)
	{
		data->fd_pipes[i] = malloc(sizeof(int) * 2);
		if (data->fd_pipes[i])
		{
			if (pipe(data->fd_pipes[i]))
				ft_pr_error(ERR_PIPE, -1, 0, 0);
		}
		else
			ft_pr_error(ERR_MALC, -1, 0, 0);
		i++;
	}
	data->fd_pipes[i] = NULL;
}

void	ft_close_pipes(t_data *data, int fl)
{
	int	i;

	i = 0;
	while (data->fd_pipes[i])
	{
		if (fl == -1)
		{
			close(data->fd_pipes[i][0]), close(data->fd_pipes[i][1]);
			printf("cl: fd[%d][0] = %d\tfd[%d][1] = %d\n", i, data->fd_pipes[i][0], i, data->fd_pipes[i][1]);
		}
		else
		{
			if (i != fl)
				close(data->fd_pipes[i][1]), printf("cl: fd[%d][1]\n", i);
			if (i + 1 != fl && data->fd_pipes[i + 1])
				close(data->fd_pipes[i + 1][0]), printf("cl: fd[%d][0]d\n", i + 1);
		}
		i++;
	}
}
