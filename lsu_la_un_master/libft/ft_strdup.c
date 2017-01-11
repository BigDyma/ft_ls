/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 10:40:30 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/28 14:48:06 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*k;
	int		i;

	i = 0;
	while (src[i])
		i++;
	k = (char*)malloc(sizeof(*src) * (i + 1));
	if (!k)
		return (NULL);
	i = 0;
	while (src[i])
	{
		k[i] = src[i];
		i++;
	}
	k[i] = '\0';
	return (k);
}
