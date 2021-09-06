#include "head_minishell.h"

int	ft_unset(t_cmd *cmd, int i)
{
	t_env	*tmp;

	while (cmd->arg[++i])
	{
		if (ft_chek_env_key(cmd->arg[i], 0))
		{
			ft_pr_error("Error: unset: not a valid identifier", 0, 0, 2);
			return (1);
		}
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
	{
		if (ft_chek_env_key(cmd->arg[i], 1))
		{
			ft_pr_error("Error: export: not a valid identifier", 0, 0, 2);
			return (1);
		}
		ft_change_env(cmd, cmd->arg[i], 0);
	}
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
		ft_pwd(cmd->data, 1, cmd);
	}
	else
	{
		if (chdir(cmd->arg[1]) == -1)
		{
			ft_pr_error(cmd->arg[1], 0, 0, 4);
			return (1);
		}
		ft_pwd(cmd->data, 1, cmd);
	}
	return (0);
}

void	ft_start_own_prog(t_cmd *cmd, int fl)
{
	if (fl == 1)
		ft_echo(cmd), ft_free_cmd(cmd);
	else if (fl == 2)
		cmd->data->ret_val = ft_pwd(cmd->data, 0, cmd), ft_free_cmd(cmd);
	else if (fl == 3)
		cmd->data->ret_val = ft_env(cmd), ft_free_cmd(cmd);
	else if (fl == 4)
		ft_exit(cmd), ft_free_cmd(cmd);
	else if (fl == 5)
		cmd->data->ret_val = ft_unset(cmd, 0), ft_free_cmd(cmd);
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
