/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:08:56 by vleida            #+#    #+#             */
/*   Updated: 2021/08/17 14:00:33 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*str;
	int		i;

	v_init_data(&data, env);
	i = 0;
	while (i < 5)
	{
		str = readline(SHELL_FW);
		printf("str : |%s|\n", str);
		add_history(str);
		// if (!ft_parsing(&data, str))
		// 	ft_run_cmd(&data);
		// ft_free_cmd_str(&data, str);
		i++;
	}
	// v_print_data(&data);
	v_free_data(&data);
	return (0);
}
