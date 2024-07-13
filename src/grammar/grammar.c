/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/13 20:20:35 by ishenriq         ###   ########.fr       */
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

char	*ft_which_sinal(char str, char *signal)
{
	if (ft_strchr("\"", str))
		signal = "\"";
	else if (ft_strchr("\'", str))
		signal = "\'";
	else
		signal = NULL;
	return (signal);
}

static int	ft_valide_quotes(char *str, int i, char *signal)
{
	int	s;

	s = 0;
	while (str[i] != '\0')
	{
		signal = ft_which_sinal(str[i++], signal);
		if (str[i] != '\0' && (ft_count_chr(signal, '\'') == 1
				|| ft_count_chr(signal, '\"') == 1))
		{
			if (str[i] != '\0' && (str[i] == '\'' || str[i] == '\"'))
				i++;
			else
			{
				while (!ft_strchr(signal, str[i]) && str[i] != '\0')
					i++;
				if (!(str[i] == '\'' || str[i] == '\"'))
					s = 1;
				if (str[i] != '\0')
					i++;
			}
		}
	}
	if (s == 1)
		return (1);
	return (0);
}

int	ft_before_brackets(t_vector *phrase)
{
	char	*str;
	size_t	pos;
	int		i;

	if (phrase->size == 1)
		return (0);
	pos = 0;
	while (pos < phrase->size - 1)
	{
		str = ft_value(phrase, pos, 0);
		if (str[0] == '(')
		{
			if (!((ft_value_int(phrase, pos, 1) & OR_AND)
				|| (ft_value_int(phrase, pos, 1) & PIPE)))
				return (1);
			str = ft_value(phrase, pos + 1, 0);
			i = 0;
			while (str[i] != '\0')
			{
				if (str[i] == '(')
					if (str[i + 1] != '\0' && ((str[i + 1] == '|')
						|| (str[i + 2] != '\0'
						&& ft_strncmp(&str[i + 1], "&&", 2) == 0)))
						return (1);
				if (str[i] == ')')
					if (str[i - 1] == '|' || str[i - 1] == '>'
						|| str[i - 1] == '<'
						|| ft_strncmp(&str[i - 2], "&&", 2) == 0)
						return (1);
				i++;
			}
		}
		pos++;
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
			|| error(ft_valide_quotes(ft_value(phrase, i, 0), 0, NULL)))
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
	if (error(ft_before_brackets(phrase)))
		return (0);
	return (1);
}
