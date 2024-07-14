/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:23:17 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/14 15:25:55 by ishenriq         ###   ########.fr       */
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
		i++;
	}
	return (0);
}

int	ft_before_brackets(t_vector *phrase, char *str, size_t pos)
{
	while (pos < phrase->size - 1)
	{
		str = ft_value(phrase, pos, 0);
		if (str[0] == '(' && pos > 1
			&& !((ft_value_int(phrase, pos - 1, 1) & OR_AND)
				|| (ft_value_int(phrase, pos - 1, 1) & PIPE)))
			return (1);
		str = ft_value(phrase, pos + 1, 0);
		if (ft_whiling(str))
			return (1);
		pos++;
	}
	return (0);
}
