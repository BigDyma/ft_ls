/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:48:54 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/10 14:48:56 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (&(((char *)s)[len]));
		len--;
	}
	return (NULL);
}
