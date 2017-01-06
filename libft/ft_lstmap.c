/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcernea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 12:40:49 by vcernea           #+#    #+#             */
/*   Updated: 2016/10/23 12:40:50 by vcernea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*prev_list;
	t_list	*new_list;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(lst->content, lst->content_size);
	if (!new_list)
		return (NULL);
	new_list = f(lst);
	prev_list = new_list;
	while (lst->next)
	{
		prev_list->next = f(lst->next);
		prev_list = prev_list->next;
		lst = lst->next;
	}
	return (new_list);
}
