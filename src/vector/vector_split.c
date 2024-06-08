/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:58:39 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/07 18:58:19 by ishenriq         ###   ########.fr       */
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
	int	j;
	t_vector	*sliced;

	if (vector == NULL)
		return((t_vector*)0) ;
	if (pos >= vector->size)
		return((t_vector*)0) ;
	sliced = ft_vector_create();
	if (!sliced)
		return ((t_vector*)0) ;
	i = vector->size;
	pos++;
	j = 0;
	while (pos < i)
	{
		ft_vector_push_back(sliced, vector->values[pos]);
		pos++;
		j++;
	}
	j--;
	while (j >= 0)
	{
		ft_vector_pop_back(vector);
		j--;
	}
	return (sliced);
}

void	ft_vector_swap(t_vector *vector, int a, int b)
{
	void *temp;

	if (a > vector->size || b > vector->size || a < 0 || b < 0)
		return ;
	temp = vector->values[a];
	vector->values[a] = vector->values[b];
	vector->values[b] = temp;
}
