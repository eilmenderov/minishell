#include "head_minishell.h"

char	*ft_find_cmd(t_data *data, char *cmd)
{
	struct stat	buf;
	int			i;
	char		*try;

	i = 0;
	while (data->env_path[i])
	{
		try = ft_strjoin(data->env_path[i], cmd);
		if (!stat(try, &buf))
			return (try);
		free(try), i++;
	}
	return (NULL);
}

void	ft_start_cmd(t_data *data)
{
	char	*cmd;
	int		pid;
	int		tmp;
	int		ex;

	data->cmd_start = malloc(sizeof(t_cmd));
	data->cmd_start->arg = ft_split(data->rez, ' ');
	cmd = ft_find_cmd(data, data->cmd_start->arg[0]);
	if (!cmd)
	{
		ft_free_split(data->cmd_start->arg), free(data->cmd_start);
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
		ex = execve(cmd, data->cmd_start->arg, data->env);
		if (data->fd_out > 0)
			dup2(1, tmp), close(tmp);
		if (ex == -1)
			exit (1);
	}
	else
		free(cmd), ft_free_split(data->cmd_start->arg), free(data->cmd_start), wait(NULL);
}

int	ft_pool_cmd(t_data *data, char *str, int *i)
{
	return (0);
}

int	ft_pool_cmd_st(t_data *data, char *str, int *i)
{
	return (0);
}
