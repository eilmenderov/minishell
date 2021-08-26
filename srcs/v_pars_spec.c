#include "head_minishell.h"

int	ft_open_app_read(t_data *data, char *f_name, int fl)
{
	int	fd;

	if (!f_name)
		return (-1);
	if (fl == 1)
		fd = open(f_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (fl == 2)
		fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (fl == 3)
		fd = open(f_name, O_RDONLY);
	free(f_name);
	if (fd == -1)
	{
		v_pr_error(strerror(errno), 0, 0, 3);
		return (-1);
	}
	if (fl == 1 || fl == 2)
		data->fd_out = fd;
	else
		data->fd_in = fd;
	return (0);
}

int	ft_general_open(t_data *data, char *str, int *i, int fl)
{
	int		j;
	char	*f_name;

	f_name = NULL;
	if ((fl == 1 || fl == 2) && data->fd_out >= 0)
		close(data->fd_out), data->fd_out = -1;
	else if (fl == 3 && data->fd_in >= 0)
		close(data->fd_in);
	if (str[*i] && (str[*i] == '|' || str[*i] == '&'))
		*i = *i + 1;
	while (str[*i] && ft_ch_for_coinc(str[*i], " \t"))
		*i = *i + 1;
	j = *i;
	while (str[*i] && !ft_ch_for_coinc(str[*i], "> <|&;"))
		f_name = ft_proc_open(data, str, i, f_name);
	if (j == *i)
	{
		v_pr_error(ERR_SH_NEWL, 0, str[*i], 1);
		return (-2);
	}
	while (str[*i] && str[*i] == ' ')
		*i = *i + 1;
	return (ft_open_app_read(data, f_name, fl));
}

int	ft_open_app_here(t_data *data, char *str, int *i, char *rez)
{
	int otv;

	if (ft_ch_for_coinc(str[*i + 2], ";><"))
	{
		v_pr_error(ERR_SH_TKN, 0, str[*i + 2], 1);
		return (-1);
	}
	if (ft_ch_for_coinc(str[*i + 2], "\0\n"))
	{
		v_pr_error(ERR_SH_NEWL, 0, str[*i + 2], 1);
		return (-2);
	}
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		*i = *i + 2;
		return (ft_general_open(data, str, i, 1));
	}
	// else if (str[*i] == '<' && str[*i + 1] == '<')
	// 	// code here_doc																return (0) or (-5);	незабудь кавычки, экранирование и $ ?
	// else
	// 	// code bash: syntax error near unexpected token `< or > or something wrong'	return (-6);
	return (0);
}

int	ft_open_file(t_data *data, char *str, int *i, char *rez)
{
	if (ft_ch_for_coinc(str[*i + 1], ";"))
	{
		v_pr_error(ERR_SH_TKN, 0, str[*i + 2], 1);
		return (-1);
	}
	if (ft_ch_for_coinc(str[*i + 1], "\0\n"))
	{
		v_pr_error(ERR_SH_NEWL, 0, str[*i + 2], 1);
		return (-2);
	}
	if (str[*i] == '>')
	{
		*i = *i + 1;
		return (ft_general_open(data, str, i, 2));
	}
	*i = *i + 1;
	return (ft_general_open(data, str, i, 3));
}

char	*ft_pool_cmd(t_data *data, char *str, int *i, char *rez)
{
	return (NULL);
}

char	*ft_pool_cmd_st(t_data *data, char *str, int *i, char *rez)
{
	return (NULL);
}

char	*ft_redir(t_data *data, char *str, int *i, char *rez)
{
	if ((str[*i] == '<' || str[*i] == '>') && (str[*i + 1] == '<' || str[*i + 1] == '>'))
	{
		if (ft_open_app_here(data, str, i, rez))
			free(rez), rez = NULL;
	}
	else if ((str[*i] == '>' || str[*i] == '<'))
	{
		if (ft_open_file(data, str, i, rez))
			free(rez), rez = NULL;
	}
	else if (str[*i] == '|')
		rez = ft_pool_cmd(data, str, i, rez);
//	else if (str[*i] == ';' || (str[*i] == '&' && str[*i + 1] == '&'))
//		rez = ft_pool_cmd_st(data, str, i, rez);
	return (rez);
}
