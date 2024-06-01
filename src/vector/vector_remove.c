/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:46:52 by phraranha         #+#    #+#             */
/*   Updated: 2024/06/01 12:51:22 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_vector_pop_back(t_vector *vector)
{
	if (vector == NULL)
		return ;
	if (ft_vector_empty(vector))
		return ;
	vector->size--;
}

void	ft_vector_pop_front(t_vector *vector)
{
	unsigned long	i;

	if (vector == NULL)
		return ;
	if (ft_vector_empty(vector))
		return ;
	i = 0;
	while (i < vector->size - 1)
	{
		vector->values[i] = vector->values[i + 1];
		++i;
	}
	vector->size--;
}

void	ft_vector_erase(t_vector *vector, unsigned long position)
{
	unsigned long	i;

	if (vector == NULL)
		return ;
	if (position >= vector->size)
		return ;
	i = position;
	while (i < vector->size - 1)
	{
		vector->values[i] = vector->values[i + 1];
		++i;
	}
	vector->size--;
}
