/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/03 13:02:43 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static int	ft_metacharacter_following(t_vector *phrase, size_t pos)
{
	if (pos < phrase->size - 1)
		if (ft_value_int(phrase, pos, 1) & REDALL)
			if (ft_value_int(phrase, pos + 1, 1) & ALLEXRED)
				return (1);
	if (pos < phrase->size - 1)
		if (ft_value_int(phrase, pos, 1) & ALLEXRED)
			if (ft_value_int(phrase, pos + 1, 1) & ALLEXRED)
				return (1);
	return (0);
}

static int	ft_metacharacter_edges(t_vector *phrase, size_t pos)
{
	if ((ft_value_int(phrase, 0, 1) & ALLEXRED) && pos == 0)
		return (1);
	if ((ft_value_int(phrase, phrase->size - 1, 1) & ALL)
		&& pos == phrase->size - 1)
		return (1);
	return (0);
}

static int	ft_valid_brackets(t_vector *phrase)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (i < phrase->size)
	{
		if ((long)ft_value_int(phrase, i, 1) & OPEN_BRACKET)
			count++;
		if ((long)ft_value_int(phrase, i, 1) & CLOSE_BRACKET)
			count--;
		if ((long)count < 0)
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
	if (ft_count_token(phrase, OPEN_BRACKET)
		== ft_count_token(phrase, CLOSE_BRACKET))
		return (0);
	return (1);
}

int	ft_grammar_rules(t_vector *phrase)
{
	size_t	i;

	i = 0;
	while (i < phrase->size)
	{
		if (error(ft_metacharacter_edges(phrase, i)
				|| error(ft_metacharacter_following(phrase, i))))
			return (0);
		i++;
	}
	if (error(ft_open_closed_brackets(phrase)) || error(ft_valid_brackets(phrase)))
		return (0);
	return (1);
}
