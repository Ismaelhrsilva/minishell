/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:23:17 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/18 18:09:24 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_whiling(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			if (str[i + 1] != '\0' && ((str[i + 1] == '|')
					|| (str[i + 2] != '\0'
						&& ft_strncmp(&str[i + 1], "&&", 2) == 0)))
				return (1);
		if (str[i] == ')' && ft_strlen(str) > 2)
			if (str[i - 1] == '|' || str[i - 1] == '>'
				|| str[i - 1] == '<'
				|| ft_strncmp(&str[i - 2], "&&", 2) == 0)
				return (1);
		if (str[i] == '(' && str[i + 1] != '\0' && str[i + 1] == ')')
			return (1);
		if (i > 0 && str[0] == '(' && str[i] == '(')
			return (1);
		i++;
	}
	return (0);
}

int	ft_before_brackets(t_vector *phrase, char *str, size_t pos)
{
	int	before;
	int	after;

	while (pos < phrase->size)
	{
		str = ft_value(phrase, pos, 0);
		if (pos > 0)
			before = ft_value_int(phrase, pos - 1, 1);
		if (pos < phrase->size - 1)
			after = ft_value_int(phrase, pos + 1, 1);
		if (str[0] == '(' && pos > 0)
			if (!(before & OR_AND || before & PIPE))
				return (1);
		if (str[0] == '(' && pos < phrase->size - 1)
			if (!(after & OR_AND || after & PIPE || after & REDALL))
				return (1);
		if (pos < phrase->size && ft_whiling(str))
			return (1);
		pos++;
	}
	return (0);
}
