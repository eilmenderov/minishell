#include "head_minishell.h"

static void	ft_first_cmd(t_cmd *cmd)
{
	int		fl;
	char	*cmd_s;

	fl = ft_buildin(cmd, 0);
	if (cmd->fd_outf > 0)
		close(cmd->data->fd_pipes[cmd->num_start][1]);
	else
		cmd->fd_outf = cmd->data->fd_pipes[cmd->num_start][1];
	cmd->data->fd_pipes[cmd->num_start][1] = -1;
	ft_redirects(cmd, 0);
	if (fl)
		ft_start_own_prog(cmd, fl);
	else
	{
		cmd_s = ft_find_cmd(cmd);
		fl = execve(cmd_s, cmd->arg, cmd->data->env), free(cmd_s);
		ft_pr_error(NULL, 0, 0, 5), cmd->data->ret_val = 1;
	}
	ft_redirects(cmd, 1);
}

static void	ft_child(t_cmd *cmd)
{
	int		fl;
	char	*cmd_s;

	fl = ft_buildin(cmd, 0);
	if (cmd->fd_inf > 0)
		close(cmd->data->fd_pipes[cmd->num_start - 1][0]);
	else
		cmd->fd_inf = cmd->data->fd_pipes[cmd->num_start - 1][0];
	cmd->data->fd_pipes[cmd->num_start - 1][0] = -1;
	if (cmd->fd_outf > 0)
		close(cmd->data->fd_pipes[cmd->num_start][1]);
	else
		cmd->fd_outf = cmd->data->fd_pipes[cmd->num_start][1];
	cmd->data->fd_pipes[cmd->num_start][1] = -1;
	ft_redirects(cmd, 0);
	if (fl)
		ft_start_own_prog(cmd, fl);
	else
	{
		cmd_s = ft_find_cmd(cmd);
		fl = execve(cmd_s, cmd->arg, cmd->data->env), free(cmd_s);
		ft_pr_error(NULL, 0, 0, 5), cmd->data->ret_val = 1;
	}
	ft_redirects(cmd, 1);
}

static void	ft_last_cmd(t_cmd *cmd)
{
	int		fl;
	char	*cmd_s;

	fl = ft_buildin(cmd, 0);
	if (cmd->fd_inf > 0)
		close(cmd->data->fd_pipes[cmd->num_start - 1][0]);
	else
		cmd->fd_inf = cmd->data->fd_pipes[cmd->num_start - 1][0];
	cmd->data->fd_pipes[cmd->num_start - 1][0] = -1;
	ft_redirects(cmd, 0);
	if (fl)
		ft_start_own_prog(cmd, fl);
	else
	{
		cmd_s = ft_find_cmd(cmd);
		fl = execve(cmd_s, cmd->arg, cmd->data->env), free(cmd_s);
		ft_pr_error(NULL, 0, 0, 5), cmd->data->ret_val = 1;
	}
	ft_redirects(cmd, 1);
}

void	ft_multiple_cmd(t_cmd *cmd, int i)
{
	int		fl;
	t_cmd	*tmp;

	ft_create_pipes(cmd->data), tmp = cmd;
	while (tmp)
	{
		if (tmp->delim != PIPE && tmp->delim != 0)
			ft_pr_error("Sorry not supported yeat", -1, 0, 0);
		fl = fork();
		if (fl < 0)
			ft_pr_error(ERR_FORK, -1, 0, 0);
		if (i < cmd->data->total_cmd && !fl)
		{
			ft_close_pipes(tmp->data, tmp, tmp->num_start);
			if (tmp == tmp->data->cmd_start)
				ft_first_cmd(tmp), exit(cmd->data->ret_val);
			else if (tmp->next)
				ft_child(tmp), exit(cmd->data->ret_val);
			ft_last_cmd(tmp), exit(cmd->data->ret_val);
		}
		cmd->data->all_pid[i] = fl;
		tmp = tmp->next, i++;
	}
	ft_close_all(cmd->data), ft_wait_all_cmd(cmd->data);
}
