/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:38:17 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 20:38:43 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_next;
	t_list	*head_new;

	if (!lst || !f || !del)
		return (0);
	head_new = ft_lstnew(f(lst->content));
	if (head_new == 0)
		return (0);
	new_next = head_new;
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
			ft_lstclear(&head_new, del);
		new_next->next = new;
		new_next = new_next->next;
		lst = lst->next;
	}
	return (head_new);
}
