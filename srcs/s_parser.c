#include "head_minishell.h"


static char 	*ft_merge_q1(char *str, int *i, char *rez)
{
	int j;

	j = *i;//начало встречи ордин кавычки
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	rez = ft_substr(str, j + 1, *i - j - 1);
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
//	printf("%s\n", rez);
//	if (!rez) ///почему-то не видит что он пустой???
//	{
//		printf("la\n");
//		rez = ft_strdup("");
//	}
	while (str[++j])
		if (!ifkey(str[j]))
			break ;
//	if (j == *i + 1)
//		return ("$\n");
	j = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\"' && str[*i] != ' ' && str[*i] != '\'' &&
	str[*i] != '|' && str[*i] != '&')
		(*i)++;

	dol = ft_substr(str, j + 1, *i - j - 1);
//	printf("dol: %s\n", dol);
	buf = data->beg_env;
	while (buf)
	{
		if (!ft_strncmp(buf->key, dol, ft_strlen(dol)))
			break ;
		buf = buf->next;
	}
	if (buf)
		rez = buf->val;
	else
		rez = ft_strdup("");
	free(dol);
	free(buf);
	return (rez);
}

static char 	*ft_merge_q2(t_data *data, char *str, int *i, char *rez)
{
	int		j;
	char	*rez_dol;

	j = *i;
//	if (!rez)
//		rez = ft_strndup(str, *i);
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			rez = ft_substr(str, j + 1, *i - j - 1);// before $
			rez_dol = ft_dollar(data, str, i, rez_dol); //$
		}
		(*i)++;
	}
	rez = ft_strjoin_m(rez, rez_dol, 3);
	return (rez);
}

char *ft_redir(t_data *data, char *str, int *i, char *rez)
{
	(void)str;
	(void)i;
	(void)data;
	return (rez);
}

char *ft_normal(char *str, int *i, char *rez)
{

	return (rez);
}

int ft_parsing(t_data *data, char *str)
{
	int		i;
	char	*rez;

	i = 0;
	while (str && str[i])
	{
		printf("%d %c\n", i, str[i]);
		if (str[i] == '\'')
			rez = ft_merge_q1(str, &i, rez);
		else if (str[i] == '$')
			rez = ft_dollar(data, str, &i, rez);
		else if (str[i] == '\"')
			rez = ft_merge_q2(data, str, &i, rez);
//		else if (ft_ch_for_coinc(str[i], "><|&\\;"))
//			rez = ft_redir(data, str, &i, rez);
		else
			rez = ft_normal(str, &i, rez);
//	 }
//		printf("%s\n", rez);
//		exit(1);
		printf("%d %c\n", i, str[i]);
//		i++;
//		exit(1);
//		sleep(1);
	}
	if (!rez)
		return (1);
	data->str_cmd = rez;
	return (0);
}