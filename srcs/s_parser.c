#include "head_minishell.h"

static char	*ft_merge_q1(char *str, int *i, char *rez)
{
	int		j;
	char	*sub;

	*i = *i + 1;
	j = *i;
	while (str[j] && str[j] != '\'')
		j++;
	sub = ft_substr(str, *i, j - *i);
	rez = ft_strjoin_m(rez, sub, 3);
	*i = j + 1;
	return (rez);
}

static char	*ft_merge_q2(t_data *data, char *str, int *i, char *rez)
{
	int		j;
	char	*sub;

	sub = NULL;
	j = *i + 1;
	while (str[++(*i)])
	{
		if (str[*i] == '\"')
			break ;
		else if (str[*i] == '$')
		{
			rez = ft_strjoin_m(rez, ft_strndup(&str[j], *i - j), 3);
			rez = ft_dollar(data, str, i, rez);
			j = *i;
			*i = *i - 1;
		}
	}
	if (j != *i)
		sub = ft_strndup(&str[j], *i - j);
	rez = ft_strjoin_m(rez, sub, 3);
	(*i)++;
	return (rez);
}

char	*ft_almost_all(t_data *data, char *str, int *i, char *rez)
{
	while (str[*i] && !ft_ch_for_coinc(str[*i], "><|&;"))
	{
		if (str[*i] == '\'')
			rez = ft_merge_q1(str, i, rez);
		else if (str[*i] == '$')
			rez = ft_dollar(data, str, i, rez);
		else if (str[*i] == '\"')
			rez = ft_merge_q2(data, str, i, rez);
		else if (str[*i] == '\\')
		{
			rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], 1), 3);
			*i = *i + 2;
		}
		else
			rez = ft_normal(str, i, rez, "><|&\\;'\"$");
	}
	return (rez);
}

char	*ft_proc_open(t_data *data, char *str, int *i, char *rez)
{
	while (str[*i] && !ft_ch_for_coinc(str[*i], "> <|&;"))
	{
		if (str[*i] == '\'')
			rez = ft_merge_q1(str, i, rez);
		else if (str[*i] == '$')
			rez = ft_dollar(data, str, i, rez);
		else if (str[*i] == '\"')
			rez = ft_merge_q2(data, str, i, rez);
		else if (str[*i] == '\\')
		{
			rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], 1), 3);
			*i = *i + 2;
		}
		else
			rez = ft_normal(str, i, rez, "> <|&\\;'\"$");
	}
	return (rez);
}

int	ft_parsing(t_data *data, char *str)
{
	int		i;
	char	*rez;

	rez = NULL;
	i = 0;
	while (str[i])
	{
		if (ft_ch_for_coinc(str[i], "><|&;"))
			rez = ft_redir(data, str, &i, rez);
		else
			rez = ft_almost_all(data, str, &i, rez);
		if (!rez)
				return (1);
	}
	// rez = ft_strjoin_m(rez, "\n", 1);
	// write (data->fd_out, rez, ft_strlen(rez));
	data->str_cmd = rez;
	// close (data->fd_out);
	// if (!rez)
	// 	return (1);
	return (0);
}
