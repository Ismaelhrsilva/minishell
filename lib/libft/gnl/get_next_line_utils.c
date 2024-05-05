/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:48:32 by ishenriq          #+#    #+#             */
/*   Updated: 2024/01/03 20:19:46 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_listg	*gnl_lstnew(void *content)
{
	t_listg	*ret;

	ret = (t_listg *)malloc(1 * sizeof(t_listg));
	if (ret == 0)
		return (0);
	ret->content = *(char *)content;
	ret->next = NULL;
	return (ret);
}

t_listg	*gnl_lstlast(t_listg *lst)
{
	if (!lst)
		return (0);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

void	gnl_lstadd_back(t_listg **lst, t_listg *new)
{
	t_listg	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = gnl_lstlast(*lst);
		last->next = new;
	}
}

int	gnl_lstsize(t_listg *lst)
{
	t_listg	*current;
	int		count;

	count = 0;
	current = lst;
	while (current != NULL)
	{
		if (current->content != '\n')
			count++;
		else
		{
			count++;
			break ;
		}
		current = current->next;
	}
	return (count);
}
