/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/23 19:00:49 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static int	ft_metacharacter_following(t_phrase *phrase, int pos)
{
	if (pos < phrase->size - 1)
		if (ft_get_token(phrase, pos) & REDALL)
			if (ft_get_token(phrase, pos + 1) & ALLEXRED)
				return (1);
	if (pos < phrase->size - 1)
		if (ft_get_token(phrase, pos) & ALLEXRED)
			if (ft_get_token(phrase, pos + 1) & ALLEXRED)
				return (1);
	return (0);
}

/*static int	ft_redirect_following(t_phrase *phrase, int pos)
{
	if (pos < phrase->size - 1)
		if (ft_get_token(phrase, pos) & REDALL)
			if (ft_get_token(phrase, pos + 1) == WORD)
				return (0);
	if (ft_get_token(phrase, pos) == WORD)
		return (0);
	return (1);
}*/

static int	ft_metacharacter_edges(t_phrase *phrase, int pos)
{
	if ((ft_get_token(phrase, 0) & ALLEXRED) && pos == 0)
		return (1);
	if ((ft_get_token(phrase, phrase->size - 1) & ALL) && pos == phrase->size - 1)
		return (1);
	return (0);
}

static int	ft_open_closed_brackets(t_phrase *phrase)
{
	if (ft_count_token(phrase, OPEN_BRACKET) == ft_count_token(phrase, CLOSE_BRACKET))
		return (0);
	return (1);
}

void	ft_grammar_rules(t_phrase *phrase)
{
	int	n;
	int i;

	i = 0;
	n = phrase->size;
	while (i < n)
	{
		if (ft_metacharacter_edges(phrase, i))
	  		ft_printf("Error_1\n");
		if (ft_metacharacter_following(phrase, i))
	  		ft_printf("Error_2\n");
		//if (ft_redirect_following(phrase, i))
	  	//	ft_printf("Error_3\n");
		i++;
	}
	if (ft_open_closed_brackets(phrase))
	 	ft_printf("Error_4\n");
}
