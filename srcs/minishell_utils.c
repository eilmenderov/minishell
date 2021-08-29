#include "head_minishell.h"

/*
**	@brief	Print errors fd = 2
**	
**	@param	str			message
**	@param	error_code	error code
**	@param	c			if fl = 1, char for message
**	@param	fl			if fl = 0 -> exit else if fl = 1 print message with c
**						else fl = 2 print str with newline
**	@return	int			counts substrings
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
void	ft_pool_env(t_data *data, char **env, int i, size_t len)
{
	t_env	*tmp;
	t_env	*buf;

	while (env && env[i])
	{
		len = ft_strlen_m(env[i], '=');
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			ft_pr_error(ERR_MALC, -1, 0, 0);
		tmp->key = ft_strndup(env[i], len);
		tmp->val = ft_strdup(&env[i][len + 1]);
		if (!tmp->val || !tmp->key)
			ft_pr_error(ERR_MALC, -1, 0, 0);
		tmp->next = NULL, i++;
		if (!data->beg_env)
		{
			data->beg_env = tmp;
			buf = data->beg_env;
		}
		else
		{
			buf->next = tmp;
			buf = buf->next;
		}
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
	data->env_path = NULL;
	data->env = env;
	data->rez = NULL;
	ft_pool_env(data, env, 0, 0), ft_proc_envp(env, data);
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
	ft_free_split(data->env_path);
	data = NULL;
}

/*
**	@brief	Prepares the environment to run with the command
**			and fills out data->env_path
**	
**	@param	env		environment
**	@param	data	struct t_data
*/
void	ft_proc_envp(char **envp, t_data *data)
{
	int		i;
	char	**rez;

	i = 0;
	rez = envp;
	while (rez[i])
	{
		if (!ft_strncmp(rez[i], "PATH=", 5))
			break ;
		i++;
	}
	rez = ft_split(&rez[i][5], ':');
	if (!rez)
		ft_pr_error(ERR_MALC, -1, 0, 0);
	i = 0;
	while (rez[i])
		rez[i] = ft_strjoin_m(rez[i], "/", 1), i++;
	data->env_path = rez;
}
