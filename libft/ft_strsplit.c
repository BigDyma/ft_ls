/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 17:13:23 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/19 17:13:25 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_strlen_char(const char *s, char c)
{
	if (*s && *s != c)
		return (ft_strlen_char(s + 1, c) + 1);
	return (0);
}

static int		ft_tablen_word(const char *s, char c)
{
	if (!*s)
		return (1);
	if (*s != c)
		return (ft_tablen_word(s + 1, c));
	while (*s && *s == c)
		s++;
	return (ft_tablen_word(s, c) + 1);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = ft_tablen_word(s, c) + 1;
	str = (char**)malloc(sizeof(char*) * size);
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			size = ft_strlen_char(s, c);
			str[i++] = ft_strsub(s, 0, size);
			s += size;
		}
		else
			++s;
	}
	str[i] = NULL;
	return (str);
}
