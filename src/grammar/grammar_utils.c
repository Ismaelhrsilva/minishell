/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/01 14:28:57 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_token(t_vector *phrase, int pos)
{
	t_vector	*word;

	if (pos < 0 || pos >= ft_vector_size(phrase))
		return (-1);
	word = phrase->values[pos];
	return (word->values[1]);
}

int	ft_count_token(t_vector *phrase, int token)
{
	t_vector		*word;
	int				count;
	unsigned long	i;

	i = 0;
	count = 0;
	while (i < ft_vector_size(phrase))
	{
		word = phrase->values[i];
		if (word->values[1] == token)
			count++;
		i++;
	}
	return (count);
}

int	ft_pos_token(t_vector *phrase, int start, int end, int token)
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
}

int	ft_pos_token_back(t_vector *phrase, int start, int end, int token)
{
	int			pos;
	t_vector	*word;

	pos = end - 1;
	while (pos >= start)
	{
		word = phrase->values[pos];
		if (*(int *)word->values[1] & token)
			return (pos);
		pos--;
	}
	return (-1);
}
