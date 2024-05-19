/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_order.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:52:51 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/19 15:48:08 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

t_word	*ft_pop_phrase(t_phrase *phrase)
{
	t_list	*aux;
	t_word	*word;

	if (!phrase->size)
		return ((t_word *)0);
	aux = phrase->words;
	word = aux->content;
	phrase->words = phrase->words->next;
	phrase->size--;
	return (word);
}

void	*ft_see_top_phrase(t_phrase *phrase)
{
	if (!phrase->size)
		return (NULL);
	return (phrase->words->content);
}

/*void	ft_cmd_order(t_phrase *phrase)
{
	int	i;

	i = 0;
	while (i < phrase->size)
	{
		if ()

	}
}*/
