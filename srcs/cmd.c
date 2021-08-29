#include "head_minishell.h"

char	*ft_find_cmd(t_data *data, char *cmd)
{
	struct stat	buf;
	int			i;
	char		*try;
	char		**env_path;

	if (cmd[0] == '.' && cmd[1] == '/') // need to do
	{
		try = ft_strdup(&cmd[2]);
		if (!stat(try, &buf))
			return (try);
	}
	env_path = ft_proc_envp(data);
	i = 0;
	while (env_path && env_path[i])
	{
		try = ft_strjoin(env_path[i], cmd);
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

void	ft_start_cmd(t_data *data)
{
	char	*cmd;
	int		pid;
	int		tmp;
	int		ex;
	t_cmd	*do_cmd;

	do_cmd = data->cmd_start;
	cmd = ft_find_cmd(data, do_cmd->arg[0]);
	if (!cmd)
	{
		ft_pr_error(do_cmd->arg[0], 0, 0, 3);
		free(cmd), ft_free_split(do_cmd->arg);
		free(do_cmd->ful_cmd), free(data->cmd_start), data->cmd_start = NULL;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		free(cmd), write(2, ERR_FORK, ft_strlen(ERR_FORK));
		return ;
	}
	if (pid == 0)
	{
		tmp = dup(1);
		if (data->fd_out > 0)
			dup2(data->fd_out, 1), close(data->fd_out);
		ex = execve(cmd, do_cmd->arg, data->env);
		if (data->fd_out > 0)
			dup2(1, tmp), close(tmp);
		if (ex == -1)
			exit (1);
	}
	else
	{
		free(cmd), ft_free_split(do_cmd->arg);
		free(do_cmd->ful_cmd), free(data->cmd_start), data->cmd_start = NULL;
		wait(NULL);
	}
}

t_cmd	*ft_pool_new_cmd(t_data *data, char *str, int *i)
{
	t_cmd	*rez;

	rez = malloc(sizeof(t_cmd));
	rez->arg = ft_split(data->rez, ' ');
	rez->cmd = rez->arg[0];
	rez->ful_cmd = data->rez;
	data->rez = NULL;
	rez->next = NULL;
	rez->pid = 0;
	if (str[*i] != 0 && str[*i] == '|' && str[*i + 1] != '|')
		rez->delim = PIPE, (*i)++;
	else if (str[*i] != 0 && str[*i] == '&' && str[*i + 1] == '&')
		rez->delim = DOB_AMPER, (*i)++, (*i)++;
	else if (str[*i] != 0 && str[*i] == '|' && str[*i + 1] == '|')
		rez->delim = DOB_PIPE, (*i)++, (*i)++;
	else if (str[*i] != 0 && str[*i]== ';')
		rez->delim = POINT_ZAP, (*i)++;
	else
		rez->delim = 0;
	return (rez);
}

int	ft_pool_cmd(t_data *data, char *str, int *i)
{
	t_cmd	*tmp;

	data->counter++;
	if (!data->cmd_start)
		data->cmd_start = ft_pool_new_cmd(data, str, i);
	else
	{
		tmp = data->cmd_start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_pool_new_cmd(data, str, i);
	}
	return (0);
}

int	ft_pool_cmd_st(t_data *data, char *str, int *i)
{
	return (0);
}
