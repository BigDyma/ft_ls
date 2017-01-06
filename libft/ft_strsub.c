/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:15:38 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/19 16:15:40 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		length;
	char		*str;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	str = NULL;
	if ((start + len) <= length)
	{
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (str)
		{
			str = ft_strncpy(str, s + start, len);
			str[len] = '\0';
		}
	}
	return (str);
}
