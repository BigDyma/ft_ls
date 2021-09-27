/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstrelet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 16:56:38 by dstrelet          #+#    #+#             */
/*   Updated: 2016/12/28 16:56:40 by dstrelet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void push(s_list	**head_ref, char  *new_data)
{
	s_list* new_node = (s_list*)malloc(sizeof(s_list));
	new_node->drum = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}
void append(s_list **head_ref, char* new_data)
{
	s_list *new_node = (s_list*)malloc(sizeof(s_list));
	s_list *last = *head_ref;
	new_node->drum = new_data;
	new_node->next = NULL;

	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}
	while (last->next != NULL)
	{
		*head_ref = new_node;
		return;
	}
	last->next = new_node;
	return;
}


void printList(s_list *ptr)
{
    while (ptr != NULL)
    {
        printf("%s->", ptr->drum);
        ptr = ptr->next;
    }
    printf("NULL\n");
}
