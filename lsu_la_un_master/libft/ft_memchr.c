/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:44:26 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/28 14:57:26 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy;

	i = 0;
	cpy = (unsigned char *)s;
	while (i < n)
	{
		if (cpy[i] == (unsigned char)c)
			return ((void*)&cpy[i]);
		i++;
	}
	return (NULL);
}
