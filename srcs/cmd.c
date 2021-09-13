#include "head_minishell.h"

static void	ft_single_cmd(t_data *data, t_cmd *cmd, int pid)
{
	char	*cmd_s;
	int		check;

	cmd_s = ft_find_cmd(cmd);
	if (!cmd_s)
	{
		ft_pr_error(cmd->arg[0], 0, 0, 3), ft_free_cmd(cmd);
		data->ret_val = 127;
		return ;
	}
	pid = fork();
	if (pid < 0)
		ft_free_cmd(cmd), free(cmd_s), ft_pr_error(ERR_FORK, 0, 0, 2);
	else if (pid == 0)
	{
		ft_redirects(cmd, 0);
		if (execve(cmd_s, cmd->arg, data->env))
			ft_redirects(cmd, 1), ft_pr_error(NULL, 0, 0, 5), exit(errno);
	}
	else
	{
		ft_free_cmd(cmd), free(cmd_s), waitpid(-1, &check, 0);
		if (check)
			data->ret_val = 1;
	}
}

void	ft_wait_all_cmd(t_data *data)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (TRUE)
	{
		waitpid(-1, &check, 0);
		if (check != 0 || i == data->total_cmd)
			break ;
		i++;
	}
	if (check)
		data->ret_val = 1;
}

void	ft_start_cmd(t_data *data)
{
	int		fl;
	t_cmd	*cmd;

	cmd = data->cmd_start;
	if (!cmd)
		return ;
	ft_signal_cmd();
	if (!cmd->next)
	{
		fl = ft_buildin(cmd, 0);
		if (fl)
		{
			ft_redirects(cmd, 0), ft_start_own_prog(cmd, fl);
			ft_redirects(cmd, 1), ft_free_cmd(cmd), data->cmd_start = NULL;
			data->count = 0;
		}
		else
			ft_single_cmd(data, cmd, -1);
		return ;
	}
	ft_multiple_cmd(cmd, 0), ft_signal();
}
