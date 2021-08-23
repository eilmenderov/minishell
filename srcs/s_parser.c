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

char	*ft_slash(char *str, int *i, char *rez)
{
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], 1), 3);
	*i = *i + 2;
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
		if (str[i] == '\'')
			rez = ft_merge_q1(str, &i, rez);
		else if (str[i] == '$')
			rez = ft_dollar(data, str, &i, rez);
		else if (str[i] == '\"')
			rez = ft_merge_q2(data, str, &i, rez);
		else if (str[i] == '\\')
			rez = ft_slash(str, &i, rez);
		// else if (ft_ch_for_coinc(str[i], "><|&;"))
		// 	rez = ft_redir(data, str, &i, rez);
		else
			rez = ft_normal(str, &i, rez, "><|&\\;'\"$");
	}
	printf("rez = |%s|\n", rez);
	data->str_cmd = rez;
	// if (!rez)
	// 	return (1);
	return (0);
}
