/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:20:59 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/16 10:19:57 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	if (!*little)
		return ((char*)big);
	while (big[i1])
	{
		i2 = 0;
		while (big[i1 + i2] && little[i2] && little[i2] == big[i1 + i2])
			i2++;
		if (!little[i2])
			return (char*)(big + i1);
		i1++;
	}
	return (NULL);
}
