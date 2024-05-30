/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/30 17:09:39 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_token(t_phrase *phrase, int pos)
{
	int	token;
	t_list *aux;

	aux = phrase->words;
	while (aux && pos >= 0)
	{
		if (pos == 0)
			token = ((t_word *)aux->content)->token;
		aux = aux->next;
		pos--;
	}
	return (token);
}

int	ft_count_token(t_phrase *phrase, int token)
{
	int	count;
	t_list *aux;

	count = 0;
	aux = phrase->words;
	while (aux)
	{
		if (token == ((t_word *)aux->content)->token)
			count++;
		aux = aux->next;
	}
	return (count);
}

/*int	ft_token_equal(t_phrase *phrase, int pos, int flag)
{
	if (ft_get_token(phrase, pos) & flag)
		return (1);
	return (0);
}*/

int	ft_pos_token(t_phrase *phrase, int start, int end, int token)
{
	int	token_pos;
	t_list *aux;
	int	pos;
	int	size;

	aux = phrase->words;
	pos = 0;
	while (aux)
	{
		token_pos = ((t_word *)aux->content)->token;
		if (pos >= start && pos < end)
			if (token_pos & token)
				return (pos);
		aux = aux->next;
		pos++;
	}
	return (-1);
}

int	ft_pos_token_back(t_phrase *phrase, int start, int end, int token)
{
	int	token_pos;
	int	pos;

	pos = phrase->size;
	while (pos--)
	{
		token_pos = ft_get_token(phrase, pos);
		if (pos >= start && pos < end)
			if (token_pos & token)
				return (pos);
	}
	return (-1);
}
