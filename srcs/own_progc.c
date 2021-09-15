#include "head_minishell.h"

void	ft_echo(t_cmd *cmd, char *s, int i)
{
	int		j;
	int 	k;

	if (cmd->fd_inf > 0)
		close(cmd->fd_inf), cmd->fd_inf = -1;
	while (s[i] && !ft_ch_for_coinc(s[i], " "))
		i++;
	i++, j = i;
	while (s[i] == '-' && s[i + 1] == 'n')
	{
		k = i;
		while (s[i + 1] == 'n')
			i++;
		if (s[i + 1] == ' ' || !s[i + 1])
			i += 2;
		else
		{
			i = k;
			break ;
		}
	}
	if (i == j)
		ft_putendl_fd(&s[i], 1), cmd->data->ret_val = 0;
	else
		ft_putstr_fd(&s[i], 1), cmd->data->ret_val = 0;
}

int	ft_pwd(t_data *data, int fl, t_cmd *cmd)
{
	char	*str;
	t_env	*tmp;

	(void)cmd;
	str = getcwd(NULL, PWD_LEN);
	str = ft_strjoin_m(NULL, str, 2);
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

int	ft_env(t_cmd *cmd)
{
	t_env	*tmp;

	if (cmd->arg[1])
	{
		ft_pr_error("Error: env: support only one arg", 0, 0, 2);
		return (127);
	}
	tmp = cmd->data->beg_env;
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

	ft_redirects(cmd, 1);
	i = ft_strlen_m(cmd->ful_cmd, ' ');
	if (!i)
		i = ft_strlen(cmd->ful_cmd);
	while (cmd->ful_cmd[i] && cmd->ful_cmd[i] == ' ')
		i++;
	j = i;
	while (cmd->ful_cmd[i] && cmd->ful_cmd[i] != ' ')
		i++;
	if (i == j)
		ft_putendl_fd("exit", 2),
		ft_free_data(cmd->data), exit(cmd->data->ret_val);
	arg = ft_strndup(&cmd->ful_cmd[j], i - j);
	ft_putendl_fd("exit", 2), i = 0;
	while (ft_isdigit(arg[i]))
		i++;
	if (!arg[i])
		cmd->data->ret_val = ft_atoi(arg);
	else
		cmd->data->ret_val = 255, ft_pr_error(arg, 1, 0, 3);
	free(arg), ft_free_data(cmd->data), exit(cmd->data->ret_val);
}

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
