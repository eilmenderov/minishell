#include "head_minishell.h"


int	ft_open_app_here(t_data *data, char *str, int *i, char *rez)
{
	int rez;
	
	if (ft_ch_for_coinc(str[*i + 2], "&|;><")
		// code bash: syntax error near unexpected token `& or | or ; or > or <'		return (-1); 
	if (ft_ch_for_coinc(str[*i + 2], " \0"))
		// code bash: syntax error near unexpected token `newline'						return (-2);
	if (str[*i] == '>' && str[*i + 1] == '>')
		// code write create append in file												return (0);	незабудь кавычки, экранирование и $
	else if (str[*i] == '<' && str[*i + 1] == '<')
		// code here_doc																return (0);	незабудь кавычки, экранирование и $ ?
	else
		// code bash: syntax error near unexpected token `< or > or something wrong'	return (-3);
}

int	ft_open_file(t_data *data, char *str, int *i, char *rez)
{
	if (ft_ch_for_coinc(str[*i + 1], "&|;")
		// code bash: syntax error near unexpected token `; or | or &'		return (-1);
	if (ft_ch_for_coinc(str[*i + 1], " \0"))
		// code bash: syntax error near unexpected token `newline'			return (-2);
	if (str[*i] == '>')
		// code write creat trunc in file									return (0);	незабудь кавычки, экранирование и $
	else if (str[*i] == '<')
		// code read from file												return (0);	незабудь кавычки, экранирование и $
	else
		// error something wrong											return (-10);
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
	if (str[*i] == '\\')
	{
		rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], 1), 3);
		*i = *i + 2;
		return (rez);
	}
	else if ((str[*i] == '<' || str[*i] == '>') && (str[*i + 1] == '<' || str[*i + 1] == '>'))
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
