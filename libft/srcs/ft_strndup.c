/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 11:25:01 by vleida            #+#    #+#             */
/*   Updated: 2021/08/17 13:09:17 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*temp;
	size_t	kol;
	size_t	i;

	if (!src)
		return (NULL);
	kol = ft_strlen(src) + 1;
	if (kol > n)
		temp = malloc(sizeof(char) * kol);
	else
		temp = malloc(sizeof(char) * (n + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
		temp[i] = src[i], i++;
	temp[i] = 0;
	return (temp);
}
