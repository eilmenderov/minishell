#include "head_minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int		i;
	char	*s;
	char	*echo_rez;

	i = 0;
	s = cmd->ful_cmd;
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

void	ft_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	ft_env(t_env *beg_env)
{
	t_env	*tmp;

	tmp = beg_env;
	while (tmp)
	{
		if (!tmp->visible)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

void	ft_exit(t_cmd *cmd)
{
	write (2, "This program(exit) is under development.\n", 41);
	return ;
	// char	*arg;
	// int		j;

	// while (s[i] && s[i] == ' ')
	// 	i++;
	// j = i;
	// while (s[i] && s[i] != ' ')
	// 	i++;
	// arg = ft_strndup(&s[j], i - j);
	// if (arg && arg[0])
	// {
	// 	ft_putendl_fd("exit", 1);
	// 	i = 0;
	// 	while (ft_isdigit(arg[i]))
	// 		i++;
	// 	if (!arg[i])
	// 		data->ret_val = ft_atoi(arg);
	// 	else
	// 		data->ret_val = 255;
	// 	ft_pr_error(arg, 1, 0, 3);
	// 	free(arg);
	// 	exit(1);
	// }
	// else
	// 	ft_putendl_fd("exit", 1), exit(1);
}

void	ft_unset(t_cmd *cmd)
{
	write (2, "This program(unset) is under development.\n", 42);
	return ;
	// t_env	*tmp;
	// t_env	*tmp2;
	// t_env	*tmp_del;
	// char	*key_unset;
	// int		j;

	// j = ++i;
	// while (s[i] && !ft_ch_for_coinc(s[i], " "))
	// 	i++;
	// key_unset = ft_strndup(&s[j], i - j);
	// tmp = data->beg_env;
	// if (!ft_strcmp(key_unset, tmp->key))
	// {
	// 	data->beg_env = tmp->next;
	// 	free(tmp->val), free(tmp->key), free(tmp), free(key_unset);
	// 	return ;
	// }
	// while (tmp->next)
	// {
	// 	if (!tmp->next->next)
	// 	{
	// 		if (!ft_strcmp(key_unset, tmp->next->key))
	// 		{
	// 			free(tmp->next->val), free(tmp->next->key);
	// 			free(tmp->next), free(key_unset);
	// 			tmp->next = NULL;
	// 			return ;
	// 		}
	// 	}
	// 	if (!ft_strcmp(key_unset, tmp->next->key))
	// 		break ;
	// 	tmp = tmp->next;
	// }
	// tmp2 = tmp;
	// tmp_del = tmp->next;
	// tmp2->next = tmp_del->next;
	// tmp_del->next = NULL;
	// free(tmp_del->val), free(tmp_del->key), free(tmp_del), free(key_unset);
}

void	ft_export(t_cmd *cmd)
{
	write (2, "This program(export) is under development.\n", 43);
	return ;
}

void	ft_cd(t_cmd *cmd)
{
	write (2, "This program(cd) is under development.\n", 39);
	return ;
}

void	ft_start_own_prog(t_cmd *cmd, int fl)
{
	if (fl == 1)
		ft_echo(cmd), ft_free_cmd(cmd);
	else if (fl == 2)
		ft_pwd(), ft_free_cmd(cmd);
	else if (fl == 3)
		ft_env(cmd->data->beg_env), ft_free_cmd(cmd);
	else if (fl == 4)
		ft_exit(cmd), ft_free_cmd(cmd);
	else if (fl == 5)
		ft_unset(cmd), ft_free_cmd(cmd);
	else if (fl == 6)
		ft_export(cmd), ft_free_cmd(cmd);
	else if (fl == 7)
		ft_cd(cmd), ft_free_cmd(cmd);
	else
		ft_pr_error("Impossible", 0, 0, 2);
}

int	ft_buildin(t_cmd *cmd)
{
	char	*command;
	int		i;

	i = 0;
	while (cmd->ful_cmd[i] && !ft_ch_for_coinc(cmd->ful_cmd[i], " "))
		i++;
	command = ft_strndup(cmd->ful_cmd, i);
	i = 0;
	if (!ft_strcmp(command, "echo"))
		i = 1;
	else if (!ft_strcmp(command, "pwd"))
		i = 2;
	else if (!ft_strcmp(command, "env"))
		i = 3;
	else if (!ft_strcmp(command, "exit"))
		i = 4;
	else if (!ft_strcmp(command, "unset"))
		i = 5;
	else if (!ft_strcmp(command, "export"))
		i = 6;
	else if (!ft_strcmp(command, "cd"))
		i = 7;
	if (command)
		free(command), command = NULL;
	return (i);
}
