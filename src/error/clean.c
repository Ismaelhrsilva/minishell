/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:09 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/10 17:34:25 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freephrase(t_vector *vector)
{
	size_t		i;
	size_t		j;
	t_vector	*innervector;

	i = 0;
	if (!vector)
		return ;
	while (i < vector->size)
	{
		j = 0;
		innervector = ((t_vector *)vector->values[i]);
		while (j < innervector->size)
		{
			free(((t_vector *)vector->values[i])->values[j]);
			j++;
		}
		free(((t_vector *)vector->values[i])->values);
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
}

void	ft_freephrase_2(t_vector *vector)
{
	size_t	i;

	i = 0;
	if (!vector)
		return ;
	while (i < vector->size)
	{
		free(((t_vector *)vector->values[i])->values[0]);
		free(((t_vector *)vector->values[i])->values[2]);
		free(((t_vector *)vector->values[i])->values);
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
}

