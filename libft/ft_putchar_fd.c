/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 16:46:38 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/21 16:46:40 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_nbr_bits(unsigned int nbr)
{
	int			i;

	i = 1;
	while ((nbr = nbr >> 1))
		i++;
	return (i);
}

void				cond2(unsigned int ch, int *i, char *buff)
{
	buff[(*i)++] = ((ch >> 18) & 7) | 240;
	buff[(*i)++] = ((ch >> 12) & 63) | 128;
}

static void			ft_putwchart(int wchar, int *len, char *buff)
{
	unsigned int	ch;
	int				n;
	int				i;

	i = 0;
	ch = (unsigned int)wchar;
	n = ft_nbr_bits(ch);
	if (n > 7 && ((*len += 1)))
	{
		if (n > 11 && ((*len += 1)))
		{
			if (n > 16 && ((*len += 2)))
				cond2(ch, &i, buff);
			else if ((*len += 1))
				buff[i++] = ((ch >> 12) & 15) | 224;
			buff[i++] = ((ch >> 6) & 63) | 128;
		}
		else if ((*len += 1))
			buff[i++] = ((ch >> 6) & 31) | 192;
		buff[i++] = (ch & 63) | 128;
	}
	else if ((*len += 1))
		buff[i++] = ch;
}

void				ft_putchar_fd(int c, int fd)
{
	char		buff2[10];
	int			i;

	i = 0;
	ft_putwchart(c, &i, buff2);
	write(fd, buff2, i);
}
