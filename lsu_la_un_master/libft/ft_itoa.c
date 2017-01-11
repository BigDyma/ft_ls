/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:54:23 by nmihalac          #+#    #+#             */
/*   Updated: 2016/12/17 09:35:02 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	st_intlen(long int value)
{
	int		len;

	len = 0;
	if (value < 0)
		len++;
	while (value)
	{
		len++;
		value /= 10;
	}
	return (len);
}

char		*ft_itoa(long int n)
{
	char			*buf;
	long int		j;

	buf = ft_strnew(st_intlen(n) + 1);
	j = st_intlen(n) - 1;
	if (buf)
	{
		if (n < 0)
		{
			buf[0] = '-';
			n *= -1;
		}
		if (n == 0)
			*buf = '0';
		while (n > 0)
		{
			buf[j] = '0' + (n % 10);
			n /= 10;
			j--;
		}
	}
	return (buf);
}
