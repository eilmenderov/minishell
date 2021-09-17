#include "head_minishell.h"

static void	ft_child_scmd(t_data *data, t_cmd *cmd, char *cmd_s)
{
	ft_redirects(cmd, 0);
	if (execve(cmd_s, cmd->arg, data->env))
	{
		ft_redirects(cmd, 1);
		if (errno != 2)
			ft_pr_error(NULL, 0, 0, 5);
		if (errno && errno != 2)
			exit(errno);
		exit(0);
	}
}

static void	ft_single_cmd(t_data *data, t_cmd *cmd, int pid)
{
	char	*cmd_s;
	int		check;

	cmd_s = ft_find_cmd(cmd, 0);
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
		ft_child_scmd(data, cmd, cmd_s);
	else
	{
		ft_free_cmd(cmd), free(cmd_s), waitpid(pid, &check, 0);
		if (errno == 2 && check)
			data->ret_val = 1;
		else if (check)
			data->ret_val = 126;
		else
			data->ret_val = 0;
	}
}

void	ft_wait_all_cmd(t_data *data)
{
	int	check;
	int	all;
	int	i;

	if (data->fl)
		return ;
	all = 0;
	check = 0;
	waitpid(data->all_pid[data->total_cmd - 1], &check, 0);
	i = 0;
	while (i < data->total_cmd - 1)
	{
		waitpid(-1, &all, 0);
		i++;
	}
	if (check)
		data->ret_val = 127;
	else
		data->ret_val = 0;
}

void	ft_start_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_start;
	if (!cmd)
		return ;
	ft_signal_cmd();
	if (!cmd->next)
	{
		cmd->fl = ft_buildin(cmd, 0);
		if (cmd->fl)
		{
			ft_redirects(cmd, 0), ft_start_own_prog(cmd, cmd->fl);
			ft_redirects(cmd, 1), ft_free_cmd(cmd), data->cmd_start = NULL;
			data->count = 0;
		}
		else
			ft_single_cmd(data, cmd, -1);
		ft_signal();
		return ;
	}
	ft_multiple_cmd(data->cmd_start, 0), ft_signal();
}
