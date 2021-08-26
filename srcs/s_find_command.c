#include "head_minishell.h"

int ft_exec(char *str_path, char **arr_com, t_data *data)
{
	int		pid;
	int 	ex;
	int 	tmp;

	pid = fork();
	if (pid < 0)
	{
		write(2, ERR_FORK, ft_strlen(ERR_FORK));
		return (2);
	}
	if (pid == 0)
	{
		tmp = dup(1);
		if (data->fd_out > 0)
		{
			dup2(data->fd_out, 1);
			close(data->fd_out);
		}
		ex = execve(str_path, arr_com, data->envp);
		if (data->fd_out > 0)
		{
			dup2(1, tmp);
			close(tmp);
		}
		if (ex == -1)
			exit (1);
	}
	else
		wait(NULL);
	return (0);
}

int	ft_arr_len(char **arr_path)
{
	int j;

	j = 0;
	while (arr_path[j])
		j++;
	return (j);
}

void ft_find_command(t_data *data, char *rez)
{
	int		i;
	char 	**arr_path;
	t_env 	*tmp;
	char 	*str_path;
	struct stat buf;

	data->cmd_start->arg = ft_split(rez, ' ');
	tmp = data->beg_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PATH", 5))
			break;
		tmp = tmp->next;
	}
	arr_path = ft_split(tmp->val, ':');
	i = 0;
	while (arr_path[i]) // находим путь с коммандой в PATH
	{
		str_path = ft_strjoin(arr_path[i], "/");
		str_path = ft_strjoin_m(str_path, data->cmd_start->arg[0], 1);
		if (stat(str_path, &buf))
		{
			free(str_path), i++;
			continue ;
		}
		ft_exec(str_path, data->cmd_start->arg, data), free(str_path);
		break ;
	}
	if (i == ft_arr_len(arr_path))
	{
		write(2, "minishell: ", 12);
		write(2, ERR_COMM, ft_strlen(ERR_COMM));
		write(2, data->cmd_start->arg[0], ft_strlen(data->cmd_start->arg[0]));
		write(2, "\n", 1);
	}
}