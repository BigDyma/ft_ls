/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmihalac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:44:14 by nmihalac          #+#    #+#             */
/*   Updated: 2016/10/24 16:51:38 by nmihalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*tmp;

	tmp = ft_memalloc(n + 1);
	tmp = ft_memcpy(tmp, src, n);
	dst = ft_memcpy(dst, tmp, n);
	free(tmp);
	return (dst);
}
