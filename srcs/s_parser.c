#include "head_minishell.h"

/* */

static char 	*ft_dollar(t_data *data, char *str, int *i)
{
	char	*rez;
	char	*dol;
	size_t	len;
	t_env 	*buf;

	rez = ft_strndup(str, *i);
	len = ft_strlen_m(&str[*i], ' ');
	if (len > ft_strlen_m(&str[*i], '\"') || !len)
		len = ft_strlen_m(&str[*i], '\"');
	dol = ft_strndup(&str[*i + 1], len - 1);
	buf = data->beg_env;
	while (buf)
	{
		if (!ft_strncmp(buf->key, dol, ft_strlen(dol)))
			break ;
		buf = buf->next;
	}
	if (buf)
		rez = ft_strjoin_m(rez, buf->val, 1);
	rez = ft_strjoin_m(rez, &str[*i + len], 1);
	free(dol);
	if (str)
		free(str), str = NULL;
	return (rez);
}

static char 	*ft_merge_q1(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin_m(tmp, tmp2, 1);
	tmp = ft_strjoin_m(tmp, tmp3, 1);
	free(tmp2), free(tmp3);
	if (str)
		free(str), str = NULL;
	return (tmp);
}

static char 	*ft_merge_q2(t_data *data, char *str, int *i)
{
	int		j;
	char 	*rez;

	(*i)++;
	j = *i;
	while (str[*i] != '\"')
	{
		if (!str[*i])
			v_pr_error("Error: qoute error\n", -2);
		if (str[*i] == '$')
			str = ft_dollar(data, str, i);
		(*i)++;
	}
	rez = ft_strjoin_m(ft_strndup(str, j - 1),
					   ft_strndup(&str[j], *i - j),3);
	rez = ft_strjoin_m(rez, ft_strdup(&str[*i + 1]), 3);
	if (str)
		free(str), str = NULL;
	return (rez);
}

int ft_parsing(t_data *data, char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			str = ft_merge_q1(str, &i);
		if (str[i] == '$')
			str = ft_dollar(data, str, &i);
		if (str[i] == '\"')
			str = ft_merge_q2(data, str, &i);
		i++;
	}
	if (!str)
		return (1);
	data->str_cmd = str;
	return (0);
}