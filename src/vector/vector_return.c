/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:57:06 by paranha           #+#    #+#             */
/*   Updated: 2024/07/02 19:38:23 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_vector_at(const t_vector *vector, unsigned long index)
{
	if (vector == NULL)
		return (0);
	if (index >= vector->size)
		return (0);
	return (vector->values[index]);
}

void	*ft_value(const t_vector *vector, unsigned long i, unsigned long j)
{
	t_vector	*inner_vector;

	if (vector == NULL)
		return (0);
	if (i >= vector->size)
		return (0);
	inner_vector = vector->values[i];
	if (inner_vector == NULL)
		return (0);
	if (j >= inner_vector->size)
		return (0);
	return (inner_vector->values[j]);
}

int	ft_value_int(const t_vector *vector, unsigned long i, unsigned long j)
{
	return (*(int *)ft_value(vector, i, j));
}

bool	ft_vector_empty(const t_vector *vector)
{
	if (vector == NULL)
		return (true);
	return (vector->size == 0);
}

unsigned long	ft_vector_size(const t_vector *vector)
{
	if (vector == NULL)
		return (-1);
	return (vector->size);
}
