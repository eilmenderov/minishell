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

	v_init_data(&data, env);
	v_print_data(&data);
	return (0);
}
