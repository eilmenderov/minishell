#include "head_minishell.h"

static void	ft_hd_helper(char *line, t_data *data)
{
	if (line)
		free(line), line = NULL;
	if (data->fd_in > 0)
		close(data->fd_in), data->fd_in = -1;
}

/*
**	@brief	Create pipe and read there from fd = 0 until stop_world
**	
**	@param	data	struct t_data
**	@param	str		string from readline
**	@param	i		where str now
*/
int	ft_here_doc(t_data *data, char *str, int *i, char *stoper)
{
	int		fd[2];
	char	*line;

	*i = *i + 2;
	while (str[*i] && str[*i] == ' ')
		*i = *i + 1;
	while (str[*i] && !ft_ch_for_coinc(str[*i], "> <|&;"))
		stoper = ft_proc_open(data, str, i, stoper);
	if (!stoper)
	{
		data->ret_val = 1, ft_pr_error(ERR_SH_NEWL, 0, 0, 2);
		return (1);
	}
	pipe(fd), line = NULL, write(1, "> ", 2);
	while (TRUE)
	{
		if (get_next_line(0, &line) == -1)
			return (ft_pr_error(ERR_GNL, -5, 0, 2));
		if (!ft_strcmp(line, stoper) || !line)
			break ;
		ft_putendl_fd(line, fd[1]), free(line), line = NULL, write(1, "> ", 2);
	}
	ft_hd_helper(line, data), close(fd[1]), data->fd_in = fd[0];
	return (0);
}
