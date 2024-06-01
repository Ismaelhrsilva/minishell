/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_return.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:47:33 by phraranha         #+#    #+#             */
/*   Updated: 2024/06/01 12:51:14 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_vector_at(const t_vector *vector, unsigned long index)
{
	if (vector == NULL)
		return (0);
	if (index >= vector->size)
		return (0);
	return ((long)(vector->values[index]));
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
