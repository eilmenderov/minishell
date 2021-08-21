#include "head_minishell.h"


static char 	*ft_merge_q1(char *str, int *i, char *rez)
{
	int j;
	char *sub;

	j = *i;//начало встречи ордин кавычки
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	sub = ft_substr(str, j + 1, *i - j - 1);
	rez = ft_strjoin_m(rez, sub, 3);
	(*i)++;
	return (rez);
}

static int ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

static char 	*ft_dollar(t_data *data, char *str, int *i, char *rez)
{
	char	*dol;
	size_t	j;
	t_env 	*buf;

	j = *i;
	while (str[++j])
		if (!ifkey(str[j]))
			break ;
//	if (j == *i + 1) //todo
//		return (rez);
	j = *i;
	(*i)++;
	while (str[*i] && !ft_ch_for_coinc(str[*i], " '\"|&"))
		(*i)++;
	dol = ft_substr(str, j + 1, *i - j - 1);
	printf("dol = %s\n", dol);
	buf = data->beg_env;
	while (buf)
	{
		if (!ft_strncmp(buf->key, dol, ft_strlen(dol)))
			break ;
		buf = buf->next;
	}
	if (buf)
		rez = ft_strjoin_m(rez, buf->val, 1);
	else
		rez = ft_strjoin_m(rez, ft_strdup(""), 3);
	free(dol);
	return (rez);
}

static char 	*ft_merge_q2(t_data *data, char *str, int *i, char *rez)
{
	int j;
	char *sub;

	j = *i + 1;
	while (str[++(*i)])
	{
		if (str[*i] == '\"')
			break ;
		else if (str[*i] == '$')
		{
			rez = ft_strjoin_m(rez, ft_strndup(&str[j], *i - j), 3);// before $
			rez = ft_dollar(data, str, i, rez); //$
			j = *i;
		}
	}
	if (j != *i)
		sub = ft_strndup(&str[j], *i - j);
	rez = ft_strjoin_m(rez, sub, 3);
	(*i)++;
	return (rez);
}

int ft_parsing(t_data *data, char *str)
{
	int		i;
	char	*rez;

	rez = NULL;
	i = 0;
	while (str && str[i])
	{
	 	 if (str[i] == '\'')
	 	 	rez = ft_merge_q1(str, &i, rez);
	 	 else if (str[i] == '$')
	 	 	rez = ft_dollar(data, str, &i, rez);
	 	 else if (str[i] == '\"')
	 	 	rez = ft_merge_q2(data, str, &i, rez);
	 	// else if (ft_ch_for_coinc(str[i], "><|&\\;"))
	 	// 	rez = ft_redir(data, str, &i, rez);
	 	 else
	 	 	rez = ft_normal(str, &i, rez, "><|&\\;\'\"$");
	}
	if (!rez)
		return (1);
	data->str_cmd = rez;
	return (0);
}