#include "head_minishell.h"

static t_env	*ft_find_key(t_env *env)
{
	t_env	*tmp;
	t_env	*elem_sort;
	char	*str_tmp;
	int		dif;

	tmp = env;
	elem_sort = tmp;
	str_tmp = NULL;
	while (tmp)
	{
		if (!tmp->print)
		{
			dif = ft_strcmp(str_tmp, tmp->key);
			if (dif > 0)
			{
				elem_sort = tmp;
				str_tmp = tmp->key;
			}
		}
		tmp = tmp->next;
	}
	elem_sort->print = 1;
	return (elem_sort);
}

static void	ft_print_export(t_env *env)
{
	t_env	*tmp;
	t_env	*elem_sort;

	tmp = env;
	while (tmp)
	{
		elem_sort = ft_find_key(env);
		if (!elem_sort->visible && elem_sort->val)
			printf("declare -x %s=\"%s\"\n", elem_sort->key, elem_sort->val);
		else if (!elem_sort->visible && !elem_sort->val)
			printf("declare -x %s\n", elem_sort->key);
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		tmp->print = 0;
		tmp = tmp->next;
	}
}

static int	ft_export(t_cmd *cmd, int i)
{
	if (!cmd->arg[1])
	{
		ft_print_export(cmd->data->beg_env);
		return (0);
	}
	while (cmd->arg[++i])
	{
		if (ft_chek_env_key(cmd->arg[i], 1))
		{
			ft_pr_error("Error: export: not a valid identifier", 0, 0, 2);
			return (1);
		}
		if (ft_strlen_m(cmd->arg[i], '='))
			ft_change_env(cmd, cmd->arg[i], 0, 0);
		else
		{
			cmd->data->beg_env->prev
				= ft_new_env(ft_strdup(cmd->arg[i]), NULL, 0);
			cmd->data->beg_env->prev->next = cmd->data->beg_env;
			cmd->data->beg_env = cmd->data->beg_env->prev;
		}
	}
	return (0);
}

void	ft_start_own_prog(t_cmd *cmd, int fl)
{
	if (fl == 1)
		ft_echo(cmd);
	else if (fl == 2)
		cmd->data->ret_val = ft_pwd(cmd->data, 0, cmd);
	else if (fl == 3)
		cmd->data->ret_val = ft_env(cmd);
	else if (fl == 4)
		ft_exit(cmd);
	else if (fl == 5)
		cmd->data->ret_val = ft_unset(cmd, 0);
	else if (fl == 6)
		cmd->data->ret_val = ft_export(cmd, 0);
	else if (fl == 7)
		cmd->data->ret_val = ft_cd(cmd);
	else if (fl == 8)
		cmd->data->ret_val
			= ft_change_env(cmd, cmd->cmd, 1, 0);
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
