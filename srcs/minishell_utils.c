#include "head_minishell.h"

t_env	*ft_new_env(char *key, char *val, unsigned char visible)
{
	t_env	*rez;

	rez = malloc(sizeof(t_env));
	if (!rez)
		ft_pr_error(ERR_MALC, -1, 0, 0);
	rez->key = key;
	rez->val = val;
	rez->visible = visible;
	rez->next = NULL;
	rez->prev = NULL;
	return (rez);
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
	char	*val;

	while (data->env && data->env[i])
	{
		len = ft_strlen_m(data->env[i], '=');
		val = ft_strdup(&data->env[i][len + 1]);
		tmp = ft_new_env(ft_strndup(data->env[i], len), val, 0);
		i++;
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
