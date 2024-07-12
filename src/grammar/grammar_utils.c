/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/12 15:27:53 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_token(t_vector *phrase, int token)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (i < phrase->size)
	{
		if (ft_value_int(phrase, i, 1) == token)
			count++;
		i++;
	}
	return (count);
}

int	ft_pos_token(t_vector *phrase, int start, int end, int token)
{
	int			pos;

	pos = start;
	while (pos < end)
	{
		if (ft_value_int(phrase, pos, 1) & token)
			return (pos);
		pos++;
	}
	return (-1);
}

int	ft_pos_token_back(t_vector *phrase, int token)
{
	int	pos;

	pos = phrase->size - 1;
	while (pos >= 0)
	{
		if (ft_value_int(phrase, pos, 1) & token)
			return (pos);
		pos--;
	}
	return (-1);
}

int	ft_bracks_inside_empty(t_vector *phrase)
{
	char	*str;
	size_t	pos;

	pos = 0;
	while (pos < phrase->size)
	{
		str = ft_value(phrase, pos, 0);
		if (str[0] == '(' && ft_strlen(str) == 2)
			return (1);
		pos++;
	}
	return (0);
}

int	error(int status)
{
	if (status)
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		ft_status(2);
		return (true);
	}
	return (false);
}
