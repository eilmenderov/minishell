#include "head_minishell.h"

static char 	*ft_merge_q1(char *str, int *i, char *rez)
{
	int		j;

	if (!rez)
		rez = ft_strndup(str, *i);
	j = *i + 1;
	while (str[j] && str[j] != '\'')
		j++;
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], j - *i - 1), 3);
	j++, *i = j;
	while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$')
		j++;
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i], j - *i), 3);
	*i = j;
	// printf("rez = |%s|\n", rez);
	return (rez);
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
	*i = j;
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
			*i = j, j--;
		}
		j++;
	}
	if (*i != j)
		rez = ft_strjoin_m(rez, ft_strndup(&str[*i + 1], j - *i - 1), 3);
	j++; *i = j;
	while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$')
		j++;
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i], j - *i), 3);
	*i = j;
	return (rez);
}

// static char	*ft_slash(char	*str, int *i, char *rez)
// {
// 	*i = *i + 1;
// 	rez = ft_strjoin_m(rez, ft_strndup(&str[*i], 1), 3);
// }

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
		else
			i++;
		// printf("i = %d str[i] = |%s| rez = |%s|\n", i, &str[i], rez);
		// if (str[i] == '\\')
		// 	rez = ft_slash(str, &i, rez);
		// printf("rez[%d] = |%s|\n", i, rez);
		
	}
	if (!rez)
		return (1);
	data->str_cmd = rez;
	return (0);
}