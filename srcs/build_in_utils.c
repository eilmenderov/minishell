#include "head_minishell.h"

void	ft_change_oldpwd(t_cmd *cmd, int fl)
{
	t_env	*tmp;

	if (!fl)
	{
		cmd->data->tmp = getcwd(NULL, PWD_LEN);
		cmd->data->tmp = ft_strjoin_m(NULL, cmd->data->tmp, 2);
	}
	else if (fl == 1)
	{
		tmp = cmd->data->beg_env;
		while (tmp && ft_strcmp(tmp->key, "OLDPWD"))
			tmp = tmp->next;
		if (tmp)
			free(tmp->val), tmp->val = cmd->data->tmp;
		else
			free(cmd->data->tmp), cmd->data->tmp = NULL;
	}
}

int	ft_cd(t_cmd *cmd, t_env *tmp)
{
	ft_change_oldpwd(cmd, 0);
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
	ft_change_oldpwd(cmd, 1);
	return (0);
}

void	ft_redirects(t_cmd *cmd, int fl)
{
	if (!fl)
	{
		ft_env_to_char(cmd->data);
		cmd->tmp_fd[1] = dup(STDOUT);
		cmd->tmp_fd[0] = dup(STDIN);
		if (cmd->fd_outf > 0)
			dup2(cmd->fd_outf, STDOUT), close(cmd->fd_outf);
		if (cmd->fd_inf > 0)
			dup2(cmd->fd_inf, STDIN), close(cmd->fd_inf);
	}
	else
	{
		ft_free_split(cmd->data->env);
		close(STDIN);
		close(STDOUT);
		dup2(cmd->tmp_fd[1], STDOUT);
		close(cmd->tmp_fd[1]), cmd->tmp_fd[1] = -1;
		dup2(cmd->tmp_fd[0], STDIN);
		close(cmd->tmp_fd[0]), cmd->tmp_fd[0] = -1;
	}
}

int	ft_chek_env_key(char *str, int fl)
{
	int	i;

	if (!str || !str[0])
		return (1);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != '_' && str[i] != '='
			&& !ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (1);
		if (str[i] == '=' && !fl)
			return (1);
		else if (str[i] == '=' && fl)
			break ;
		i++;
	}
	return (0);
}

int	ft_change_env(t_cmd *cmd, char *str, int visib, int len)
{
	char	*key;
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
	if (ft_chek_env_key(cmd->cmd, 1))
	{
		ft_pr_error(cmd->arg[0], 0, 0, 3);
		return (1);
	}
	tmp = ft_new_env(key, ft_strdup(&str[len + 1]), visib);
	tmp->next = cmd->data->beg_env;
	cmd->data->beg_env->prev = tmp;
	cmd->data->beg_env = tmp;
	return (0);
}
