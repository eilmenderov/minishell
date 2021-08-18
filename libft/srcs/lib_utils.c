/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:16:52 by vleida            #+#    #+#             */
/*   Updated: 2021/08/16 15:19:46 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_m(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	if (!c)
	{
		while (str[i])
			i++;
	}
	else
	{
		while (str[i] && str[i] != (unsigned char)c)
			i++;
		if (!str[i])
			i = 0;
	}
	return (i);
}

char	*ft_strjoin_m(char const *s1, char const *s2, int c)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*rez;

	len = ft_strlen_m(s1, 0) + ft_strlen_m(s2, 0);
	rez = malloc(sizeof(char) * (len + 1));
	if (!rez)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		rez[i] = s1[i], i++;
	j = 0;
	while (s2 && s2[j])
		rez[i] = s2[j], i++, j++;
	rez[i] = 0;
	if (s1 && (c == 1 || c == 3))
		free ((char *)s1), s1 = NULL;
	if (s2 && (c == 2 || c == 3))
		free ((char *)s2), s2 = NULL;
	return (rez);
}

int	ft_gnl_cheker(char *ost)
{
	int	i;

	if (!ost)
		return (1);
	i = 0;
	while (*(ost + i) && *(ost + i) != '\n')
		i++;
	if (*(ost + i) == '\n')
		return (0);
	return (1);
}
