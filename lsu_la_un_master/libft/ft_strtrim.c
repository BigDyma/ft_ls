/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:54:07 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/28 15:02:11 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isblank_custom(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	char	*fresh;
	int		index_end;
	size_t	i;

	if (!s)
		return (NULL);
	index_end = 0;
	i = 0;
	fresh = ft_strnew(ft_strlen(s) + 4);
	while (i < ft_strlen(s))
	{
		if (!index_end && ft_isblank_custom(s[i]))
			i++;
		else
			fresh[index_end++] = s[i++];
	}
	while (ft_isblank_custom(fresh[--index_end]))
		fresh[index_end] = '\0';
	return (fresh);
}
