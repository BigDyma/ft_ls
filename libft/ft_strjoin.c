/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:22:12 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/19 16:22:14 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	length;

	newstr = NULL;
	if (s1 && s2)
	{
		length = ft_strlen(s1) + ft_strlen(s2);
		newstr = (char *)malloc(sizeof(char) * (length + 1));
		if (newstr)
		{
			ft_strcpy(newstr, s1);
			ft_strcat(newstr, s2);
		}
	}
	return (newstr);
}
