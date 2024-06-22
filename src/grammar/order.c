/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:25:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 20:43:07 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_not_ordered_redall(t_vector *vector)
{
	int	i;

	i = 0;
	while (i < vector->size - 2)
	{
		if (ft_value_int(vector, i, 1) & (ALL_W_BRACKET & ~REDALL))
			return (0);
		if (ft_value_int(vector, i, 1) & REDALL
			&& ft_value_int(vector, i + 1, 1) == WORD
			&& ft_value_int(vector, i + 2, 1) == WORD)
			return (1);
		i++;
	}
	return (0);
}

static void	ft_order_aux(t_vector *vector, int i)
{
	if (i > vector->size - 3 || vector->size <= 2)
		return ;
	if (ft_value_int(vector, i, 1) & REDALL)
	{
		if (ft_value_int(vector, i + 2, 1) == 0)
		{
			ft_vector_insert(vector, i, vector->values[i + 2]);
			ft_vector_erase(vector, i + 3);
			if (ft_not_ordered_redall(vector))
				ft_order_aux(vector, 0);
		}
	}
	else if (ft_value_int(vector, i, 1) & (ALL_W_BRACKET & ~REDALL))
		ft_order_aux(vector, i + 1);
	ft_order_aux(vector, i + 1);
}

void	ft_order_redall(t_vector *vector)
{
	ft_order_aux(vector, 0);
}
