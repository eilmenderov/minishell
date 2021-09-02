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
	/* problem with numeric argument required(try exit asd in bash) */
	char	*arg;
	int		j;
	int		i;

	i = ft_strlen_m(cmd->ful_cmd, ' ');
	while (cmd->ful_cmd[i] && cmd->ful_cmd[i] == ' ')
		i++;
	j = i;
	while (cmd->ful_cmd[i] && cmd->ful_cmd[i] != ' ')
		i++;
	arg = ft_strndup(&cmd->ful_cmd[j], i - j);
	if (arg && arg[0])
	{
		ft_putendl_fd("exit", 1);
		i = 0;
		while (ft_isdigit(arg[i]))
			i++;
		if (!arg[i])
			cmd->data->ret_val = ft_atoi(arg);
		else
			cmd->data->ret_val = 255;
		// ft_pr_error(arg, 1, 0, 3);
		free(arg);
		exit(1);
	}
	else
		ft_putendl_fd("exit", 1), free(arg), exit(1);
}

void	ft_unset(t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (cmd->arg[i])
	{
		tmp = cmd->data->beg_env;
		while (tmp && ft_strcmp(tmp->key, cmd->arg[i]))
			tmp = tmp->next;
		if (!tmp)
			continue ;
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		free(tmp->key), tmp->key = NULL;
		free(tmp->val), tmp->val = NULL;
		free(tmp), tmp = NULL;
		i++;
	}
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
	int		fl;

	fl = 0;
	while (cmd->ful_cmd[fl] && !ft_ch_for_coinc(cmd->ful_cmd[fl], " "))
		fl++;
	command = ft_strndup(cmd->ful_cmd, fl);
	fl = 0;
	if (!ft_strcmp(command, "echo"))
		fl = 1;
	else if (!ft_strcmp(command, "pwd"))
		fl = 2;
	else if (!ft_strcmp(command, "env"))
		fl = 3;
	else if (!ft_strcmp(command, "exit"))
		fl = 4;
	else if (!ft_strcmp(command, "unset"))
		fl = 5;
	else if (!ft_strcmp(command, "export"))
		fl = 6;
	else if (!ft_strcmp(command, "cd"))
		fl = 7;
	if (command)
		free(command), command = NULL;
	return (fl);
}
