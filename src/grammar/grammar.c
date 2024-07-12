/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/12 15:27:58 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_which_sinal(char str, char *signal, int *s)
{
	if (ft_strchr("\"", str))
	{
		signal = "\"";
		*s = 1;
	}
	else if (ft_strchr("\'", str))
	{
		signal = "\'";
		*s = 1;
	}
	return (signal);
}

static int	ft_valide_quotes(t_vector *phrase, size_t pos, int i, int s)
{
	char	*signal;
	char	*str;

	signal = NULL;
	str = ft_value(phrase, pos, 0);
	while (str[i] != '\0')
	{
		signal = ft_which_sinal(str[i], signal, &s);
		i++;
		if (ft_count_chr(signal, '\'') == 1 || ft_count_chr(signal, '\"') == 1)
		{
			while (!ft_strchr(signal, str[i]) && str[i] != '\0')
				i++;
			if (str[i] == '\'' || str[i] == '\"')
				s = 0;
			if (s == 1)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int	ft_grammar_rules(t_vector *phrase)
{
	size_t	i;

	i = 0;
	while (i < phrase->size)
	{
		if (error(ft_metacharacter_edges(phrase, i))
			|| error(ft_metacharacter_following(phrase, i))
			|| error(ft_valide_quotes(phrase, i, 0, 0)))
			return (0);
		i++;
	}
	if (error(ft_error_brackets(-1)))
	{
		ft_error_brackets(0);
		return (0);
	}
	if (error(ft_bracks_inside_empty(phrase)))
		return (0);
	return (1);
}
