#include "head_minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int		i;
	char	*s;

	i = 0;
	s = cmd->ful_cmd;
	while (s[i] && !ft_ch_for_coinc(s[i], " "))
		i++;
	i++, ft_redirects_before(cmd);
	if (s[i] == '-' && s[i + 1] == 'n')
		ft_putstr_fd(&s[i + 3], 1);
	else
		ft_putendl_fd(&s[i], 1);
	ft_redirects_after(cmd), cmd->data->ret_val = 0;
}

int	ft_pwd(t_data *data, int fl, t_cmd *cmd)
{
	char	*str;
	t_env	*tmp;

	str = getcwd(NULL, PWD_LEN);
	str = ft_strjoin_m(NULL, str, 2);
	if (!fl)
	{
		ft_redirects_before(cmd);
		printf("%s\n", str), free(str);
		ft_redirects_after(cmd);
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
	ft_redirects_before(cmd);
	tmp = cmd->data->beg_env;
	while (tmp)
	{
		if (!tmp->visible && tmp->val)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	ft_redirects_after(cmd);
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
