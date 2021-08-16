/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:11:50 by vleida            #+#    #+#             */
/*   Updated: 2021/08/16 15:10:41 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					neg;
	unsigned long long	res;

	neg = 1;
	res = 0;
	while (*str && (*str == 32 || (*str > 8 && *str < 14)))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9' && res <= FT_ATOI_MN)
		res = res * 10 + (*str - 48), str++;
	if (res > FT_ATOI_MV && neg == 1)
		return (-1);
	else if (res > FT_ATOI_MV && neg == -1)
		return (0);
	return ((int)res * neg);
}
