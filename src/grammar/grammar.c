/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/08 17:01:47 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_metacharacter_following(t_vector *phrase, int pos)
{
	if (pos < ft_vector_size(phrase) - 1)
		if (ft_value_int(phrase, pos, 1) & REDALL)
			if (ft_value_int(phrase, pos + 1, 1) & ALLEXRED)
				return (1);
	if (pos < ft_vector_size(phrase) - 1)
		if (ft_value_int(phrase, pos, 1) & ALLEXRED)
			if (ft_value_int(phrase, pos + 1, 1) & ALLEXRED)
				return (1);
	return (0);
}

static int	ft_metacharacter_edges(t_vector *phrase, int pos)
{
	if ((ft_value_int(phrase, 0, 1) & ALLEXRED) && pos == 0)
		return (1);
	if ((ft_value_int(phrase, ft_vector_size(phrase) - 1, 1) & ALL)
		&& pos == ft_vector_size(phrase) - 1)
		return (1);
	return (0);
}

static int	ft_valid_brackets(t_vector *phrase)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < phrase->size)
	{
		if (ft_value_int(phrase, i, 1) & OPEN_BRACKET)
			count++;
		if (ft_value_int(phrase, i, 1) & CLOSE_BRACKET)
			count--;
		if (count < 0)
			return (1);
		i++;
	}
	if (count == 0)
		return (0);
	else
		return (1);
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
	if (ft_valid_brackets(phrase))
		ft_printf("Error: Mismatched brackets\n");
}
