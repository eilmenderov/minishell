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

void	ft_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->beg_env;
	while (tmp)
	{
		if (!tmp->visible)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

void	ft_pwd(t_data *data)
{
	printf("%s\n", getenv("PWD"));
}

void	ft_unset(t_data *data, char *s, int i)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*tmp_del;
	char	*key_unset;
	int		j;

	j = ++i;
	while (s[i] && !ft_ch_for_coinc(s[i], " "))
		i++;
	key_unset = ft_strndup(&s[j], i - j);
	tmp = data->beg_env;
	if (!ft_strcmp(key_unset, tmp->key))
	{
		data->beg_env = tmp->next;
		free(tmp->val), free(tmp->key), free(tmp), free(key_unset);
		return ;
	}
	while (tmp->next)
	{
		if (!tmp->next->next)
		{
			if (!ft_strcmp(key_unset, tmp->next->key))
			{
				free(tmp->next->val), free(tmp->next->key);
				free(tmp->next), free(key_unset);
				tmp->next = NULL;
				return ;
			}
		}
		if (!ft_strcmp(key_unset, tmp->next->key))
			break ;
		tmp = tmp->next;
	}
	tmp2 = tmp;
	tmp_del = tmp->next;
	tmp2->next = tmp_del->next;
	tmp_del->next = NULL;
	free(tmp_del->val), free(tmp_del->key), free(tmp_del), free(key_unset);
}

void ft_exit(t_data *data, char *s, int i)
{
	char	*arg;
	int 	j;
	int 	ret;

//	j = i;
	while (s[i] && s[i] == ' ')
		i++;
	j = i;
	while (s[i] && s[i] != ' ')
		i++;
	arg = ft_strndup(&s[j], i - j);
	if (arg)
	{
		ft_putendl_fd("exit", 1);
//		if (ft_atoi(arg))
//			data->ret_val =
		ft_pr_error(arg, 1, 0, 3);
		free(arg);
		exit(1);
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
		ft_echo(data), ft_free_cmd(data->cmd_start, s_0);
		return (1);
	}
//	else if (!ft_strcmp(s_0, "cd"))
//		ft_cd(data), return (1);
	else if (!ft_strcmp(s_0, "pwd"))
	{
		ft_pwd(data), ft_free_cmd(data->cmd_start, s_0);
		return (1);
	}
//	else if (!ft_strcmp(s_0, "export"))
//		ft_export(data), return (1);
	else if (!ft_strcmp(s_0, "unset"))
	{
		ft_unset(data, s, i), ft_free_cmd(data->cmd_start, s_0);
		return (1);
	}
	else if (!ft_strcmp(s_0, "env"))
	{
		ft_env(data), ft_free_cmd(data->cmd_start, s_0);
		return (1);
	}
	else if (!ft_strcmp(s_0, "exit"))
	{
		ft_exit(data, s, i), ft_free_cmd(data->cmd_start, s_0);
		return (1);
	}
	if (s_0)
		free(s_0);
	return (0);
}
