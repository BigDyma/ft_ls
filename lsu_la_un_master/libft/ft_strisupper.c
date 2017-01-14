/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:33:05 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/19 14:33:06 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisupper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isupper(str[i]))
			return (0);
		i++;
	}
	return (1);
}