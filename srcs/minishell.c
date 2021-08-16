/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:08:56 by vleida            #+#    #+#             */
/*   Updated: 2021/08/16 17:16:47 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	main(void)
{
	int fd = open("tmp", O_APPEND | O_WRONLY | O_CREAT, 0777);
	dup2(fd, 1);
	close(fd);
	printf("rez = %s\n", ft_itoa(1203012));
	return (0);
}
