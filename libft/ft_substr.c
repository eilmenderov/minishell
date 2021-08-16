/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:53:00 by vleida            #+#    #+#             */
/*   Updated: 2021/04/22 14:41:30 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*rez;
	unsigned int	i;

	if (!s)
		return (NULL);
	rez = malloc(sizeof(char) * len + 1);
	if (!rez)
		return (NULL);
	rez[0] = 0;
	if (ft_strlen(s) <= start)
		return (rez);
	i = 0;
	while (start + i < start + len)
	{
		rez[i] = s[start + i];
		i++;
	}
	rez[i] = 0;
	return (rez);
}
