/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:45:54 by phraranha         #+#    #+#             */
/*   Updated: 2024/06/01 12:52:23 by phraranha        ###   ########.org.br   */
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
