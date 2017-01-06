/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 17:04:36 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/16 10:20:14 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len3;
	size_t	len1;
	size_t	tmp;

	len3 = ft_strlen(little);
	len1 = ft_strlen(big);
	tmp = 0;
	if (!little)
		return (char*)(big);
	while (tmp + len3 <= len && tmp + len3 <= len1)
	{
		if (!ft_strncmp(big, little, len3))
			return ((char*)big);
		big++;
		tmp++;
	}
	return (NULL);
}
