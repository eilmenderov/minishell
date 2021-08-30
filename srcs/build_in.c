#include "head_minishell.h"

void	ft_echo(t_data *data)
{
	int		i;
	char	*s;
	char	*echo_rez;

	i = 0;
	s = data->cmd_start->ful_cmd;
	while (s[i] && !ft_ch_for_coinc(s[i], " "))
		i++;
	i++;
	if (s[i] == '-' && s[i + 1] == 'n')
	{
		echo_rez = ft_strdup(&s[i + 3]);
		printf("%s", echo_rez), free(echo_rez);
	}
	else
	{
		echo_rez = ft_strdup(&s[i]);
		printf("%s\n", echo_rez), free(echo_rez);
	}
}

int	ft_buildin(t_data *data)
{
	int		i;
	char	*s;
	char	*s_0;

	i = 0;
	s = data->cmd_start->ful_cmd;
	while (s[i] && !ft_ch_for_coinc(s[i], " "))
		i++;
	s_0 = ft_strndup(s, i);
	if (!ft_strcmp(s_0, "echo"))
	{
		ft_echo(data);
		ft_free_cmd(data, data->cmd_start, s_0);
		return (1);
	}
//	else if (!ft_strcmp(s_0, "cd"))
//		ft_cd(data), return (1);
//	else if (!ft_strcmp(s_0, "pwd"))
//		ft_pwd(data), return (1);
//	else if (!ft_strcmp(s_0, "export"))
//		ft_export(data), return (1);
//	else if (!ft_strcmp(s_0, "unset"))
//		ft_unset(data), return (1);
//	else if (!ft_strcmp(s_0, "env"))
//		ft_env(data), return (1);
//	else if (!ft_strcmp(s_0, "exit"))
//		ft_exit(data), return (1);
	return (0);
}
