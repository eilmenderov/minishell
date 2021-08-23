#include "head_minishell.h"

char	*ft_dol_helper(char *key, t_env *env, char *rez)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
		tmp = tmp->next;
	free(key), key = NULL;
	if (tmp)
		rez = ft_strjoin_m(rez, tmp->val, 1);
	return (rez);
}

char	*ft_normal(char *str, int *i, char *rez, char *stop)
{
	int	j;

	j = *i;
	while (str[j] && !ft_ch_for_coinc(str[j], stop))
		j++;
	if (*i != j)
		rez = ft_strjoin_m(rez, ft_strndup(&str[*i], j - *i), 3);
	*i = j;
	return (rez);
}
