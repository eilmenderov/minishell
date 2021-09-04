#include "head_minishell.h"

char	*ft_points(t_cmd *do_cmd)
{
	int		i;
	char	*rez;
	t_env	*tmp;

	if (ft_ch_for_coinc(do_cmd->cmd[0], "./"))
		return (ft_strdup(do_cmd->cmd));
	tmp = do_cmd->data->beg_env;
	while (tmp && ft_strcmp(tmp->key, "HOME"))
		tmp = tmp->next;
	if (tmp)
	{
		rez = ft_strjoin_m(tmp->val, ft_strdup(&do_cmd->cmd[1]), 2);
		free(do_cmd->arg[0]);
		do_cmd->arg[0] = ft_strdup(rez);
		do_cmd->cmd = do_cmd->arg[0];
		return (rez);
	}
	return (NULL);
}

char	*ft_find_cmd(t_cmd *do_cmd)
{
	struct stat	buf;
	int			i;
	char		*try;
	char		**env_path;

	if (ft_ch_for_coinc(do_cmd->cmd[0], "./~"))
	{
		try = ft_points(do_cmd);
		return (try);
	}
	env_path = ft_proc_envp(do_cmd->data);
	i = 0;
	while (env_path && env_path[i])
	{
		try = ft_strjoin(env_path[i], do_cmd->cmd);
		if (!stat(try, &buf))
		{
			ft_free_split(env_path), env_path = NULL;
			return (try);
		}
		free(try), i++;
	}
	if (env_path)
		ft_free_split(env_path), env_path = NULL;
	return (NULL);
}

void	ft_free_cmd(t_cmd *do_cmd)
{
	t_cmd	*tmp;

	if (do_cmd->fd_infile > 0)
		close(do_cmd->fd_infile), do_cmd->fd_infile = -1;
	if (do_cmd->fd_outfile > 0)
		close(do_cmd->fd_outfile), do_cmd->fd_outfile = -1;
	if (do_cmd->arg)
		ft_free_split(do_cmd->arg), do_cmd->arg = NULL;
	if (do_cmd->ful_cmd)
		free(do_cmd->ful_cmd), do_cmd->ful_cmd = NULL;
	tmp = do_cmd->next;
	do_cmd->data->cmd_start = tmp;
	free(do_cmd), do_cmd = NULL;
}

void	ft_single_cmd(t_data *data, t_cmd *do_cmd, int pid, int ex)
{
	/* Doesn't work with '<' redirects infile, yeat!!! in work!! */
	char	*cmd;
	int		tmp;

	cmd = ft_find_cmd(do_cmd);
	if (!cmd)
	{
		ft_pr_error(do_cmd->arg[0], 0, 0, 3), ft_free_cmd(do_cmd), free(cmd);
		return ;
	}
	pid = fork();
	if (pid < 0)
		ft_free_cmd(do_cmd), free(cmd), write(2, ERR_FORK, ft_strlen(ERR_FORK));
	else if (pid == 0)
	{
		tmp = dup(1);
		if (do_cmd->fd_outfile > 0)
			dup2(do_cmd->fd_outfile, 1), close(do_cmd->fd_outfile);
		ex = execve(cmd, do_cmd->arg, data->env);
		if (do_cmd->fd_outfile > 0)
			dup2(1, tmp), close(tmp);
		if (ex == -1)
			exit (1);
	}
	else
		ft_free_cmd(do_cmd), free(cmd), wait(NULL);
}

void	ft_multiple_cmd(t_cmd *cmd)
{
	return ;
}

void	ft_start_cmd(t_data *data)
{
	int	fl;

	if (!data->cmd_start->next)
	{
		fl = ft_buildin(data->cmd_start, 0);
		if (fl)
			ft_start_own_prog(data->cmd_start, fl);
		else
			ft_single_cmd(data, data->cmd_start, -1, -1);
		return ;
	}
	ft_multiple_cmd(data->cmd_start);
}

t_cmd	*ft_pool_new_cmd(t_data *data, char *str, int *i)
{
	t_cmd	*rez;

	rez = malloc(sizeof(t_cmd));
	rez->arg = ft_split(data->rez, ' ');
	rez->cmd = rez->arg[0];
	rez->ful_cmd = data->rez;
	rez->data = data;
	rez->fd_infile = data->fd_in;
	rez->fd_outfile = data->fd_out;
	data->rez = NULL;
	rez->next = NULL;
	rez->pid = 0;
	if (str[*i] != 0 && str[*i] == '|' && str[*i + 1] != '|')
		rez->delim = PIPE, (*i)++;
	else if (str[*i] != 0 && str[*i] == '&' && str[*i + 1] == '&')
		rez->delim = DOB_AMPER, (*i)++, (*i)++;
	else if (str[*i] != 0 && str[*i] == '|' && str[*i + 1] == '|')
		rez->delim = DOB_PIPE, (*i)++, (*i)++;
	else if (str[*i] != 0 && str[*i] == ';')
		rez->delim = POINT_ZAP, (*i)++;
	else
		rez->delim = 0;
	return (rez);
}

int	ft_pool_cmd(t_data *data, char *str, int *i)
{
	t_cmd	*tmp;

	if (!data->cmd_start)
		data->cmd_start = ft_pool_new_cmd(data, str, i);
	else
	{
		tmp = data->cmd_start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_pool_new_cmd(data, str, i);
	}
	if (data->fd_in > 0)
		data->fd_in = -1;
	if (data->fd_out > 0)
		data->fd_out = -1;
	return (0);
}
