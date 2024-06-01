/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/01 13:35:10 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_metacharacter_following(t_vector *phrase, int pos)
{
	if (pos < ft_vector_size(phrase) - 1)
		if (ft_get_token(phrase, pos) & REDALL)
			if (ft_get_token(phrase, pos + 1) & ALLEXRED)
				return (1);
	if (pos < ft_vector_size(phrase) - 1)
		if (ft_get_token(phrase, pos) & ALLEXRED)
			if (ft_get_token(phrase, pos + 1) & ALLEXRED)
				return (1);
	return (0);
}

static int	ft_metacharacter_edges(t_vector *phrase, int pos)
{
	if ((ft_get_token(phrase, 0) & ALLEXRED) && pos == 0)
		return (1);
	if ((ft_get_token(phrase, ft_vector_size(phrase) - 1) & ALL)
		&& pos == ft_vector_size(phrase) - 1)
		return (1);
	return (0);
}

static int	ft_open_closed_brackets(t_vector *phrase)
{
	if (ft_count_token(phrase, OPEN_BRACKET) == ft_count_token(phrase, CLOSE_BRACKET))
		return (0);
	return (1);
}

void	ft_grammar_rules(t_vector *phrase)
{
	unsigned long	i;

	i = 0;
	while (i < ft_vector_size(phrase))
	{
		if (ft_metacharacter_edges(phrase, i))
			ft_printf("Error: Metacharacter at edges\n");
		if (ft_metacharacter_following(phrase, i))
			ft_printf("Error: Metacharacters following each other\n");
		i++;
	}
	if (ft_open_closed_brackets(phrase))
		ft_printf("Error: Mismatched brackets\n");
}
