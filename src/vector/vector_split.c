/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:58:39 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/01 19:00:12 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vector	*ft_vector_slice_left(t_vector *vector, unsigned long pos)
{
	unsigned long	i;
	t_vector	*sliced;

	if (vector == NULL)
		return((t_vector*)0) ;
	if (pos >= vector->size)
		return((t_vector*)0) ;
	sliced = ft_vector_create();
	if (!sliced)
		return ((t_vector*)0) ;
	i = 0;
	while (i < pos)
	{
		ft_vector_push_back(sliced, vector->values[i]);
		ft_vector_pop_front(vector);
		i++;
	}
	return (sliced);
}

t_vector	*ft_vector_slice_right(t_vector *vector, unsigned long pos)
{
	unsigned long	i;
	t_vector	*sliced;

	if (vector == NULL)
		return((t_vector*)0) ;
	if (pos >= vector->size)
		return((t_vector*)0) ;
	sliced = ft_vector_create();
	if (!sliced)
		return ((t_vector*)0) ;
	i = vector->size;
	while (pos < i)
	{
		ft_vector_push_back(sliced, vector->values[pos]);
		ft_vector_pop_back(vector);
		pos++;
	}
	return (sliced);
}
