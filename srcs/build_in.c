#include "head_minishell.h"

int	ft_echo(t_cmd *cmd)
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
	return (0);
}

int	ft_pwd(t_data *data, int fl)
{
	char	*str;
	t_env	*tmp;

	str = ft_calloc(PWD_LEN, sizeof(char));
	getcwd(str, PWD_LEN), str = ft_strjoin_m(NULL, str, 2);
	if (!fl)
	{
		printf("%s\n", str), free(str);
		return (0);
	}
	tmp = data->beg_env;
	while (tmp && ft_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	if (tmp)
		free(tmp->val), tmp->val = str;
	else
		free(str);
	return (0);
}

int	ft_env(t_env *beg_env)
{
	t_env	*tmp;

	tmp = beg_env;
	while (tmp)
	{
		if (!tmp->visible && tmp->val)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_exit(t_cmd *cmd)
{
	char	*arg;
	int		j;
	int		i;

	i = ft_strlen_m(cmd->ful_cmd, ' ');
	if (!i)
		i = ft_strlen(cmd->ful_cmd);
	while (cmd->ful_cmd[i] && cmd->ful_cmd[i] == ' ')
		i++;
	j = i;
	while (cmd->ful_cmd[i] && cmd->ful_cmd[i] != ' ')
		i++;
	if (i == j)
		ft_putendl_fd("exit", 1), exit(0);
	arg = ft_strndup(&cmd->ful_cmd[j], i - j);
	ft_putendl_fd("exit", 1), i = 0;
	while (ft_isdigit(arg[i]))
		i++;
	if (!arg[i])
		cmd->data->ret_val = ft_atoi(arg);
	else
		cmd->data->ret_val = 255, ft_pr_error(arg, 1, 0, 3);
	free(arg), exit(cmd->data->ret_val);
}

int	ft_unset(t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (cmd->arg[++i])
	{
		tmp = cmd->data->beg_env;
		while (tmp && ft_strcmp(tmp->key, cmd->arg[i]))
			tmp = tmp->next;
		if (!tmp)
			continue ;
		if (!tmp->prev)
			cmd->data->beg_env = tmp->next;
		else
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		free(tmp->key), tmp->key = NULL;
		free(tmp->val), tmp->val = NULL;
		free(tmp), tmp = NULL;
	}
	return (0);
}

void	ft_print_export(t_env *env)
{
	return ;
}

int	ft_export(t_cmd *cmd)
{
	int	i;

	if (!cmd->arg[1])
	{
		ft_print_export(cmd->data->beg_env);
		return (0);
	}
	i = 0;
	while (cmd->arg[++i])
		ft_change_env(cmd, cmd->arg[i], 0);
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	t_env	*tmp;

	if (!cmd->arg[1] || !ft_strcmp(cmd->arg[1], "~"))
	{
		tmp = cmd->data->beg_env;
		while (tmp && ft_strcmp("HOME", tmp->key))
			tmp = tmp->next;
		if (chdir(tmp->val) == -1)
		{
			ft_pr_error(cmd->arg[1], 0, 0, 4);
			return (1);
		}
		ft_pwd(cmd->data, 1);
	}
	else
	{
		if (chdir(cmd->arg[1]) == -1)
		{
			ft_pr_error(cmd->arg[1], 0, 0, 4);
			return (1);
		}
		ft_pwd(cmd->data, 1);
	}
	return (0);
}

int	ft_change_env(t_cmd *cmd, char *str, int visib)
{
	char	*key;
	int		len;
	t_env	*tmp;

	len = ft_strlen_m(str, '=');
	key = ft_strndup(str, len);
	tmp = cmd->data->beg_env;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	if (tmp)
	{
		if (tmp->val)
			free(tmp->val);
		tmp->val = ft_strdup(&str[len + 1]), free(key);
		return (0);
	}
	tmp = ft_new_env(key, ft_strdup(&str[len + 1]), visib);
	tmp->next = cmd->data->beg_env;
	cmd->data->beg_env->prev = tmp;
	cmd->data->beg_env = tmp;
	return (0);
}

void	ft_start_own_prog(t_cmd *cmd, int fl)
{
	if (fl == 1)
		cmd->data->ret_val = ft_echo(cmd), ft_free_cmd(cmd);
	else if (fl == 2)
		cmd->data->ret_val = ft_pwd(cmd->data, 0), ft_free_cmd(cmd);
	else if (fl == 3)
		cmd->data->ret_val = ft_env(cmd->data->beg_env), ft_free_cmd(cmd);
	else if (fl == 4)
		ft_exit(cmd), ft_free_cmd(cmd);
	else if (fl == 5)
		cmd->data->ret_val = ft_unset(cmd), ft_free_cmd(cmd);
	else if (fl == 6)
		cmd->data->ret_val = ft_export(cmd), ft_free_cmd(cmd);
	else if (fl == 7)
		cmd->data->ret_val = ft_cd(cmd), ft_free_cmd(cmd);
	else if (fl == 8)
		cmd->data->ret_val = ft_change_env(cmd, cmd->cmd, 1), ft_free_cmd(cmd);
	else
		ft_pr_error("Impossible", 0, 0, 2);
}

int	ft_buildin(t_cmd *cmd, int fl)
{
	fl = 0;
	if (!ft_strcmp(cmd->cmd, "echo"))
		fl = 1;
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		fl = 2;
	else if (!ft_strcmp(cmd->cmd, "env"))
		fl = 3;
	else if (!ft_strcmp(cmd->cmd, "exit"))
		fl = 4;
	else if (!ft_strcmp(cmd->cmd, "unset"))
		fl = 5;
	else if (!ft_strcmp(cmd->cmd, "export"))
		fl = 6;
	else if (!ft_strcmp(cmd->cmd, "cd"))
		fl = 7;
	else if (ft_strlen_m(cmd->cmd, '='))
		fl = 8;
	return (fl);
}
