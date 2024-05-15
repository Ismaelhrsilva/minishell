/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:17:19 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/15 19:50:03 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static t_word	*ft_construct_word(char *str, int n)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return ((t_word *)0);
	word->word = str;
	word->token = n;
	return (word);
}

t_phrase	*ft_construct_phrase(char **split, int m)
{
	t_phrase *phrase;
	t_word	*token;
	int	i;

	phrase = malloc(sizeof(t_phrase));
	if (!phrase)
		return ((t_phrase *) 0);
	phrase->words = NULL;
	phrase->size = 0;
	i = 0;
	while (i < m)
	{
		token = ft_construct_word(split[i], ft_set_token(split[i]));
		if (i == 0)
			phrase->words	= ft_lstnew(token);
		else
			ft_lstadd_back(&phrase->words, ft_lstnew(token));
		phrase->size++;
		i++;
	}
	/*while (phrase->words)
	{
		ft_printf("----------------------------------------------\n");
		ft_printf("word: %s\n", ((t_word *)phrase->words->content)->word);
		ft_printf("token: %d\n", ((t_word *)phrase->words->content)->token);
		ft_printf("----------------------------------------------\n");
		phrase->words = phrase->words->next;
	}*/
	return (phrase);
}
