/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:00:07 by vleida            #+#    #+#             */
/*   Updated: 2021/08/17 14:00:40 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	v_pr_error(char *str, int error_code)
{
	write(2, str, ft_strlen_m(str, 0));
	exit(error_code);
}

void	v_pool_env(t_data *data, char **env, int i)
{
	size_t	len;
	t_env	*tmp;
	t_env	*buf;

	while (env && env[i])
	{
		len = ft_strlen_m(env[i], '=');
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			v_pr_error("Error : malloc error\n", -1);
		tmp->key = ft_strndup(env[i], len);
		tmp->val = ft_strdup(&env[i][len + 1]);
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

void	v_init_data(t_data *data, char **env)
{
	t_env	*tmp;

	data->error = 0;
	v_pool_env(data, env, 0);
}

void	v_free_data(t_data *data)
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
	if (data->str_cmd)
		free(data->str_cmd);
}

void	v_print_data(t_data *data)
{
	t_env	*tmp;

	printf("err_fl = %d\n", data->error);
	tmp = data->beg_env;
	while (tmp)
	{
		printf("%-30s%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}
