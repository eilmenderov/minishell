#include "head_minishell.h"

int	ft_append_file(t_data *data, char *str, int *i)
{
	int		j;
	char	*f_name;

	if (data->fd_out >= 0)
		close(data->fd_out);
	while (str[*i] && &str[*i] == ' ')
		*i = *i + 1;
	j = *i;
	while (str[j] && ft_ch_for_coinc(str[j], " |&;"))
		j++;
	if (j == *i)
	{
		v_pr_error(ERR_SH_NEWL, 0, str[*i], 1);
		return (-2);
	}
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
	if (ft_ch_for_coinc(str[*i + 2], " |&"))
		// ??? " |&"																	return (-3); warning " |&"
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		*i = *i + 2;																	//return (0) or (-4);	незабудь кавычки, экранирование и $ 
		return (ft_append_file(data, str, i));
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
		// code here_doc																return (0) or (-5);	незабудь кавычки, экранирование и $ ?
	else
		// code bash: syntax error near unexpected token `< or > or something wrong'	return (-6);
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
	if (ft_ch_for_coinc(str[*i + 2], " |&"))
		// ??? " |&"														return (-3); warning " |&"
	if (str[*i] == '>')
		// code write creat trunc in file									return (0) or (-4);	незабудь кавычки, экранирование и $
	else if (str[*i] == '<')
		// code read from file												return (0) or (-5);	незабудь кавычки, экранирование и $ ?
	else
		// error something wrong											return (-7);
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
		ft_open_app_here(data, str, i, rez);
	else if ((str[*i] == '>' || str[*i] == '<'))
		ft_open_file(data, str, i, rez);
	else if (str[*i] == '|')
		rez = ft_pool_cmd(data, str, i, rez);
	else if (str[*i] == ';' || (str[*i] == '&' && str[*i + 1] == '&'))
		rez = ft_pool_cmd_st(data, str, i, rez);
	else
		return (NULL);
	return (rez);
}
