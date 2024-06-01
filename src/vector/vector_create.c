/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:49:24 by phraranha         #+#    #+#             */
/*   Updated: 2024/06/01 12:56:44 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= original_size)
		return (ptr);
	else
	{
		new = malloc(new_size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		ft_memcpy(new, ptr, original_size);
		free(ptr);
		return (new);
	}
}

t_vector	*ft_vector_create(void)
{
	t_vector	*new_vector;

	new_vector = malloc(sizeof * new_vector);
	if (new_vector == NULL)
		return (NULL);
	new_vector->size = 0;
	new_vector->capacity = FT_VECTOR_INITIAL_CAPACITY;
	new_vector->values = malloc(new_vector->capacity * sizeof(void *));
	if (new_vector->values == NULL)
	{
		free(new_vector);
		return (NULL);
	}
	return (new_vector);
}

void	ft_vector_init(t_vector *vector)
{
	free(vector->values);
	vector->values = NULL;
	vector->capacity = 0;
	vector->size = 0;
}

bool	ft_vector_resize(t_vector *vector, unsigned long new_capacity)
{
	void	*new_values;

	if (!vector)
		return (false);
	if ((int)new_capacity < 0)
		return (false);
	if (new_capacity == 0)
	{
		ft_vector_init(vector);
		return (true);
	}
	if (new_capacity < vector->size)
		new_capacity = vector->size;
	new_values = ft_realloc(vector->values, vector->capacity * sizeof(void *),
			new_capacity * sizeof(long));
	if (new_values == NULL)
		return (false);
	vector->values = new_values;
	vector->capacity = new_capacity;
	if (new_capacity < vector->size)
		vector->size = new_capacity;
	return (true);
}

void	ft_vector_free(t_vector *vector)
{
	if (vector == NULL)
		return ;
	free(vector->values);
	free(vector);
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
