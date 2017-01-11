/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:33:12 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/19 14:33:13 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strndup(const char *s, size_t n)
{
	char	*res;
	size_t	i;

	if (s == 0)
		return (0);
	res = ft_strnew(n);
	if (res == 0)
		return (0);
	i = 0;
	while (i < n && s[i] != 0)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}
