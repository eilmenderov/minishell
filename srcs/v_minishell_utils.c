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

void	v_pool_env(t_data *data, char **env)
{
	int		i;
	size_t	len;
	t_env	*tmp;
	t_env	*buf;

	buf = data->beg_env;
	i = 0;
	while (env && env[i])
	{
		len = ft_strlen_m(env[i], '=');
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			v_pr_error("Error : malloc error\n", -1);
		tmp->key = ft_strndup(env[i], len);
		tmp->val = ft_strdup(&env[i][len + 1]);
		tmp->next = NULL;
		i++;
	}
}

void	v_init_data(t_data *data, char **env)
{
	data->error = 0;
	v_pool_env(data, env);
}

void	v_print_data(t_data *data)
{
	t_env	*tmp;

	printf("err_fl = %d\n", data->error);
	tmp = data->beg_env;
	while (tmp)
	{
		printf("%s\t\t\t\t\t\t%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}
