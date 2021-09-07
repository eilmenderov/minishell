#include "head_minishell.h"

static void	ft_single_cmd(t_data *data, t_cmd *cmd, int pid)
{
	char	*cmd_s;
	int		check;

	cmd_s = ft_find_cmd(cmd);
	if (!cmd_s)
	{
		ft_pr_error(cmd->arg[0], 0, 0, 3), ft_free_cmd(cmd), free(cmd_s);
		data->ret_val = 1;
		return ;
	}
	pid = fork();
	if (pid < 0)
		ft_free_cmd(cmd), free(cmd_s), ft_pr_error(ERR_FORK, 0, 0, 2);
	else if (pid == 0)
	{
		ft_redirects_before(cmd);
		if (execve(cmd_s, cmd->arg, data->env))
			ft_redirects_after(cmd), ft_pr_error(STERR, 0, 0, 5), exit(1);
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
	data->ret_val = check;
	usleep (300);
	printf("check = %d\n", check);
}

void	ft_start_cmd(t_data *data)
{
	int	fl;

	ft_signal_cmd();
	if (!data->cmd_start->next)
	{
		fl = ft_buildin(data->cmd_start, 0);
		if (fl)
			ft_start_own_prog(data->cmd_start, fl);
		else
			ft_single_cmd(data, data->cmd_start, -1);
		return ;
	}
	ft_multiple_cmd(data->cmd_start);
}
