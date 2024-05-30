/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_order.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:52:51 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/26 18:50:17 by ishenriq         ###   ########.fr       */
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

t_word	*ft_pop_pos_phrase(t_phrase *phrase, int pos)
{
	t_list	*aux;
	t_list	*temp;
	t_word	*word;

	if (!phrase->size)
		return ((t_word *)0);
	aux = phrase->words;
	while (aux && pos >= 0)
	{
		temp = aux;
		if (pos == 0)
		{
			word = aux->content;
			temp->next = aux->next;
			//phrase->size--;
			//free(aux);
			return (word);
		}
		pos--;
		aux = aux->next;
	}
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
