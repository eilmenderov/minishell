/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:59:23 by vleida            #+#    #+#             */
/*   Updated: 2021/04/22 14:18:54 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*buf;

	if (lst && f)
	{
		buf = lst;
		while (buf)
		{
			f(buf->content);
			buf = buf->next;
		}
	}
}
