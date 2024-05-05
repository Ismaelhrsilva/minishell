/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:36:06 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 20:36:08 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*head;

	if (!lst || !del)
		return ;
	head = *lst;
	next = *lst;
	while (next)
	{
		head = head->next;
		ft_lstdelone(next, del);
		next = head;
	}
	*lst = 0;
}
