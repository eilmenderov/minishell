#include "head_minishell.h"

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
}

void	ft_child(t_cmd *cmd)
{
	int	fl;

	fl = ft_buildin(cmd, 0);
	printf("_______________________________________\n");
	printf("num = %d\tfl = %d\tcmd = %s\n", cmd->num_start, fl, cmd->ful_cmd);
	printf("---------------------------------------\n");
	ft_print_fd(cmd->data);
	if (fl)
	{
		ft_start_own_prog(cmd, fl);
	}
}

void	ft_last_cmd(t_cmd *cmd)
{
	int	fl;

	fl = ft_buildin(cmd, 0);
	printf("_______________________________________\n");
	printf("num = %d\tfl = %d\tcmd = %s\n", cmd->num_start, fl, cmd->ful_cmd);
	printf("---------------------------------------\n");
	ft_print_fd(cmd->data);
	if (fl)
	{
		ft_start_own_prog(cmd, fl);
	}
}

void	ft_multiple_cmd(t_cmd *cmd)
{
	int		pid;
	t_cmd	*tmp;

	printf("----multiple_start----\n");
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
			ft_close_pipes(tmp->data, tmp, tmp->num_start);
			if (tmp->next)
				ft_child(tmp), exit(cmd->data->ret_val);
			ft_last_cmd(tmp), exit(cmd->data->ret_val);
		}
		tmp = tmp->next;
	}
	ft_close_pipes(cmd->data, cmd, -1);
	ft_wait_all_cmd(cmd->data);
	printf("----multiple_finish----\n");
}
