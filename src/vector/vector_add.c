/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:45:54 by phraranha         #+#    #+#             */
/*   Updated: 2024/06/21 21:00:21 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_vector_push_back(t_vector *vector, void *value)
{
	unsigned long	new_capacity;

	if (vector == NULL)
		return ;
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return ;
	}
	vector->values[vector->size] = value;
	vector->size++;
}

void	ft_vector_push_front(t_vector *vector, void *value)
{
	unsigned long	new_capacity;
	unsigned long	i;

	if (vector == NULL)
		return ;
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return ;
	}
	i = vector->size;
	while (i > 0)
	{
		vector->values[i] = vector->values[i - 1];
		i--;
	}
	vector->values[0] = value;
	vector->size++;
}

unsigned long	ft_vector_insert(t_vector *vector, unsigned long position,
		void *value)
{
	unsigned long	new_capacity;
	unsigned long	i;

	if (vector == NULL)
		return (0);
	if (position > vector->size)
		return (0);
	if (vector->size >= vector->capacity)
	{
		new_capacity = vector->capacity + (vector->capacity >> 1);
		if (!ft_vector_resize(vector, new_capacity))
			return (0);
	}
	i = vector->size;
	while (i > position)
	{
		vector->values[i] = vector->values[i - 1];
		--i;
	}
	vector->values[position] = value;
	vector->size++;
	return (position);
}

void	ft_vector_reserve(t_vector *vector, unsigned long new_capacity)
{
	if (vector == NULL)
		return ;
	if (new_capacity > vector->capacity)
	{
		if (!ft_vector_resize(vector, new_capacity))
			return ;
	}
}
