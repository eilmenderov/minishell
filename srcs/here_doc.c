#include "head_minishell.h"

/*
**	@brief	Create pipe and read there from fd = 0 until stop_world
**	
**	@param	data	struct t_data
**	@param	str		string from readline
**	@param	i		where str now
*/
int	ft_here_doc(t_data *data, char *str, int *i)
{
	int		fd[2];
	char	*line;
	char	*stoper;

	*i = *i + 2;
	stoper = NULL;
	while (str[*i] && str[*i] == ' ')
		*i = *i + 1;
	while (str[*i] && !ft_ch_for_coinc(str[*i], "> <|&;"))
		stoper = ft_proc_open(data, str, i, stoper);
	pipe(fd), line = NULL, write(1, "> ", 2);
	while (TRUE)
	{
		if (get_next_line(0, &line) == -1)
			return (ft_pr_error(ERR_GNL, -5, 0, 2));
		if (!ft_strcmp(line, stoper) || !line)
			break ;
		ft_putstr_fd(line, fd[1]), free(line), line = NULL, write(1, "> ", 2);
	}
	if (line)
		free(line), line = NULL;
	if (data->fd_in > 0)
		close(data->fd_in), data->fd_in = -1;
	ft_putstr_fd("\n", fd[1]), close(fd[1]), data->fd_in = fd[0];
	return (0);
}
