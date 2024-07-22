/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:58:39 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/22 18:10:03 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vector	*ft_vector_slice_right(t_vector *vector, unsigned long pos)
{
	unsigned long	i;
	int				j;
	t_vector		*sliced;

	if (vector == NULL || pos >= vector->size)
		return ((t_vector *)0);
	sliced = ft_vector_create();
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
