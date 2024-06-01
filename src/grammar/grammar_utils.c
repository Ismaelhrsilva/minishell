/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/01 19:14:11 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_token(t_vector *phrase, int token)
{
	int				count;
	unsigned long	i;

	i = 0;
	count = 0;
	while (i < ft_vector_size(phrase))
	{
		if (ft_value_int(phrase, i, 1) == token)
			count++;
		i++;
	}
	return (count);
}

/*int	ft_pos_token(t_vector *phrase, int start, int end, int token)
{
	t_vector	*word;
	int			pos;

	pos = start;
	while (pos < end)
	{
		word = phrase->values[pos];
		if (*(int *)word->values[1] & token)
			return (pos);
		pos++;
	}
	return (-1);
}*/

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
