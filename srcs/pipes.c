#include "head_minishell.h"

void	ft_create_pipes(t_data *data)
{
	int	i;

	data->fd_pipes = malloc(sizeof(int *) * (data->total_cmd));
	i = 0;
	while (i < data->total_cmd - 1)
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

void	ft_close_pipes(t_data *data, t_cmd *cmd, int pipe_num)
{
	int	i;

	i = 0;
	pipe_num -= 1;
	while (data->fd_pipes[i] && data->fd_pipes[i + 1])
	{
		if (i != pipe_num)
			close(data->fd_pipes[i + 1][1]), data->fd_pipes[i + 1][1] = -1;
		i++;
	}
	if (data->fd_pipes[0] && pipe_num != -1)
		close(data->fd_pipes[0][1]), data->fd_pipes[0][1] = -1;
	i = 0;
	while (data->fd_pipes[i])
	{
		if (i != pipe_num)
			close(data->fd_pipes[i][0]), data->fd_pipes[i][0] = -1;
		i++;
	}
	if (cmd->fd_inf > 0)
		close(data->fd_pipes[pipe_num][0]), data->fd_pipes[pipe_num][0] = -1;
	pipe_num++;
	if (cmd->fd_outf > 0)
		close(data->fd_pipes[pipe_num][1]), data->fd_pipes[pipe_num][1] = -1;
}
