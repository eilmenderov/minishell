#include "head_minishell.h"

static char	*ft_quotes(char *str, int *i, char *rez)
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

static char	*ft_double_quotes(t_data *data, char *str, int *i, char *rez)
{
	int		j;

	*i = *i + 1;
	j = *i;
	while (str[*i])
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
		*i = *i + 1;
	}
	if (j != *i)
		rez = ft_strjoin_m(rez, ft_strndup(&str[j], *i - j), 3);
	*i = *i + 1;
	return (rez);
}

void	ft_hadle_str(t_data *data, char *str, int *i)
{
	while (str[*i] && !ft_ch_for_coinc(str[*i], "> <|&;"))
	{
		if (str[*i] == '\'')
			data->rez = ft_quotes(str, i, data->rez);
		else if (str[*i] == '$')
			data->rez = ft_dollar(data, str, i, data->rez);
		else if (str[*i] == '\"')
			data->rez = ft_double_quotes(data, str, i, data->rez);
		else if (str[*i] == '\\')
		{
			data->rez = ft_strjoin_m(data->rez, ft_strndup(&str[*i + 1], 1), 3);
			*i = *i + 2;
		}
		else
			data->rez = ft_normal(str, i, data->rez, "> <|&\\;'\"$");
	}
}

char	*ft_proc_open(t_data *data, char *str, int *i, char *rez)
{
	while (str[*i] && !ft_ch_for_coinc(str[*i], "> <|&;"))
	{
		if (str[*i] == '\'')
			rez = ft_quotes(str, i, rez);
		else if (str[*i] == '$')
			rez = ft_dollar(data, str, i, rez);
		else if (str[*i] == '\"')
			rez = ft_double_quotes(data, str, i, rez);
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
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_ch_for_coinc(str[i], "><|&;"))
		{
			if (ft_redir(data, str, &i))
				return (1);
		}
		else if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			if (data->rez && str[i] != 0)
				data->rez = ft_strjoin_m(data->rez, " ", 1);
		}
		else
			ft_hadle_str(data, str, &i);
	}
	if (data->rez)
		ft_pool_cmd(data, str, &i);
	return (0);
}
