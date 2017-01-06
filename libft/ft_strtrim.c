/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:56:06 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/19 16:56:08 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblankc(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	char	*new;
	int		endi;
	size_t	i;

	if (!s)
		return (NULL);
	endi = 0;
	i = 0;
	new = ft_strnew(ft_strlen(s));
	while (i < ft_strlen(s))
	{
		if (!endi && ft_isblankc(s[i]))
			i++;
		else
			new[endi++] = s[i++];
	}
	while (ft_isblankc(new[--endi]))
		new[endi] = '\0';
	return (new);
}
