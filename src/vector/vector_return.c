/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:47:33 by phraranha         #+#    #+#             */
/*   Updated: 2024/06/01 15:23:22 by ishenriq         ###   ########.fr       */
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
	t_vector *inner_vector;
	
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
	return (ft_value(vector, i, j));
}

unsigned long	ft_vector_size(const t_vector *vector)
{
	if (vector == NULL)
		return (-1);
	return (vector->size);
}

unsigned long	ft_vector_capacity(const t_vector *vector)
{
	if (vector == NULL)
		return (0);
	return (vector->capacity);
}

bool	ft_vector_empty(const t_vector *vector)
{
	if (vector == NULL)
		return (true);
	return (vector->size == 0);
}
