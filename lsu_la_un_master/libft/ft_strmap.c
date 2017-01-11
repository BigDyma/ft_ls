/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:52:59 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/10 14:53:02 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*fresh;

	if (!s || !f)
		return (NULL);
	fresh = ft_strnew(ft_strlen(s));
	i = 0;
	while (s[i])
	{
		fresh[i] = (*f)(s[i]);
		i++;
	}
	return (fresh);
}
