/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:53:54 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/10 14:53:57 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*out;

	out = NULL;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		out = (char *)malloc(sizeof(char) * (len + 1));
		if (out)
		{
			ft_strcpy(out, s1);
			ft_strcat(out, s2);
		}
	}
	return (out);
}
