#include "head_minishell.h"


char	*ft_redir(t_data *data, char *str, int *i, char *rez)
{
	// | > < & \ ;
	// if (str[*i] == '|')
	// 	ft_pool_cmd(data, rez);
	return (rez);
}

char	*ft_normal(char *str, int *i, char *rez)
{
	int	j;

	j = *i;
	while (str[j])
	{
		if (ft_ch_for_coinc(str[j], "><|&\\;\'\"$"))
			break;
		j++;
	}
	rez = ft_strjoin_m(rez, ft_strndup(&str[*i], j), 3);
	*i = j;
	return (rez);
}