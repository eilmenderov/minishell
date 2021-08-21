#include "head_minishell.h"

static char 	*ft_merge_q1(char *str, int *i, char *rez)
{
	char	*tmp;
	int		j;

	j = *i + 1;
	while (str[j] != '\'')
	{
		if (!str[j])
			return (NULL);
		j++;
	}
	if (!rez)
		tmp = ft_strndup(str, *i);
	tmp = ft_strjoin_m(tmp, ft_strndup(&str[*i + 1], j - *i - 1), 3);
	j++;
	*i = j;
	while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$')
		j++;
	tmp = ft_strjoin_m(tmp, ft_strndup(&str[*i], j - *i), 3);
	*i = j - 1;
	return (tmp);
}

static char 	*ft_dollar(t_data *data, char *str, int *i, char *rez)
{
	char	*dol;
	size_t	j;
	t_env 	*buf;

	j = *i;
	if (!rez)
		rez = ft_strndup(str, *i);
	while (str[j] && str[j] != '\"' && str[j] != ' ')
		j++;
	dol = ft_strndup(&str[*i + 1], j - *i - 1);
	buf = data->beg_env;
	while (buf)
	{
		if (!ft_strncmp(buf->key, dol, ft_strlen(dol)))
			break ;
		buf = buf->next;
	}
	if (buf)
		rez = ft_strjoin_m(rez, buf->val, 1);
	free(dol), *i = j;
	while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$')
		j++;
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i], j - *i), 3);
	*i = j - 1;
	return (rez);
}

static char 	*ft_merge_q2(t_data *data, char *str, int *i, char *rez)
{
	int		j;

	if (!rez)
		rez = ft_strndup(str, *i);
	j = *i + 1;
	while (str[j] && str[j] != '\"')
	{
		if (str[j] == '$')
		{
			rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], j - *i - 1), 3);
			rez = ft_dollar(data, str, &j, rez);
			*i = j;
		}
		j++;
	}
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], j - *i - 1), 3);
	j++, *i = j;
	while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$')
		j++;
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i], j - *i), 3);
	*i = j - 1;
	return (rez);
}

/*
**		@brief		Parses commands string
**		@return	int		0 if string correct, else error status
*/

char *ft_redir(t_data *data, char *str, int *i, char *rez)
{
	(void)str;
	(void)i;
	(void)data;
	return (rez);
}

char *ft_normal(char *str, int *i, char *rez)
{
	(void)str;
	(void)i;
	return (rez);
}

int ft_parsing(t_data *data, char *str)
{
	int		i;
	char	*rez;

	i = 0;
	 while (str && str[i])
	 {
	 	if (str[i] == '\'')
	 		rez = ft_merge_q1(str, &i, rez);
	 	else if (str[i] == '$')
	 		rez = ft_dollar(data, str, &i, rez);
	 	else if (str[i] == '\"')
	 		rez = ft_merge_q2(data, str, &i, rez);
//	 	else if (ft_ch_for_coinc(str[i], "><|&\\;"))
//	 		rez = ft_redir(data, str, &i, rez);
	 	else
	 		rez = ft_normal(str, &i, rez);
	 }
	rez = ft_strdup(str);
	if (!rez)
		return (1);
	data->str_cmd = rez;
	return (0);
}