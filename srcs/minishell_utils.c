#include "head_minishell.h"

/*
**	@brief	Print errors fd = 2
**	
**	@param	str			message
**	@param	error_code	error code
**	@param	c			if fl = 1, char for message
**	@param	fl			if fl = 0 -> exit else if fl = 1 print message with c
**						else fl = 2 print str with newline
**	@return	int			error_code value
*/
int	ft_pr_error(char *str, int error_code, char c, int fl)
{
	if (!fl)
		ft_putendl_fd(str, 2), exit(error_code);
	else if (fl == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\'', 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("'", 2);
	}
	else if (fl == 2)
		ft_putendl_fd(str, 2);
	else if (fl == 3)
	{
		ft_putstr_fd("minishell: ", 2), ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
	}
	return (error_code);
}

/*
**	@brief	Prepares the environment for using
**	
**	@param	data	struct t_data
**	@param	env		environment
**	@param	i 0		iterator(just because of the norm)
**	@param	len	0	iterator(just because of the norm)
*/
void	ft_pool_env(t_data *data, int i, size_t len)
{
	t_env	*tmp;
	t_env	*buf;

	while (data->env && data->env[i])
	{
		len = ft_strlen_m(data->env[i], '=');
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			ft_pr_error(ERR_MALC, -1, 0, 0);
		tmp->key = ft_strndup(data->env[i], len);
		tmp->visible = 0;
		tmp->val = ft_strdup(&data->env[i][len + 1]);
		tmp->next = NULL, i++;
		if (!data->beg_env)
		{
			data->beg_env = tmp;
			data->beg_env->prev = NULL;
			buf = data->beg_env;
			continue ;
		}
		buf->next = tmp;
		tmp->prev = buf;
		buf = buf->next;
	}
}

/*
**	@brief	Initializes struct data
**	
**	@param	data	struct t_data
**	@param	env		environment
*/
void	ft_init_data(t_data *data, char **env)
{
	t_env	*tmp;

	data->error = 0;
	data->fd_in = -1;
	data->fd_out = -1;
	data->env = env;
	data->rez = NULL;
	ft_pool_env(data, 0, 0);
	tmp = data->beg_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			data->shlvl = ft_atoi(tmp->val) + 1;
			free(tmp->val), tmp->val = ft_itoa(data->shlvl);
			break ;
		}
		tmp = tmp->next;
	}
}

/*
**	@brief	Free memory which was allocated
**	
**	@param	data	struct t_data
*/
void	ft_free_data(t_data *data)
{
	t_env	*tmp;
	t_env	*buf;

	tmp = data->beg_env;
	data->beg_env = NULL;
	while (tmp)
	{
		if (tmp->key)
			free(tmp->key), tmp->key = NULL;
		if (tmp->val)
			free(tmp->val), tmp->val = NULL;
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
	data = NULL;
}

/*
**	@brief	Prepares the environment to run with the command
**			and fills out data->env_path
**	
**	@param	env		environment
**	@param	data	struct t_data
*/
char	**ft_proc_envp(t_data *data)
{
	t_env	*tmp;
	int		i;
	char	**rez;

	tmp = data->beg_env;
	while (tmp && ft_strcmp(tmp->key, "PATH"))
		tmp = tmp->next;
	rez = ft_split(tmp->val, ':');
	if (!rez)
		ft_pr_error(ERR_MALC, -1, 0, 0);
	i = 0;
	while (rez[i])
		rez[i] = ft_strjoin_m(rez[i], "/", 1), i++;
	return (rez);
}
