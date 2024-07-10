/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:01:50 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/10 19:02:14 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_ast(t_node	*root)
{
	if (root)
	{
		if (root->left)
			ft_clear_ast(root->left);
		if (root->right)
			ft_clear_ast(root->right);
		ft_inside_ast(root);
		if (root)
			free(root);
	}
}

void	clean_vector(t_vector *vector)
{
	size_t	i;

	i = 0;
	while (i < vector->size)
	{
		free(ft_vector_at(vector, i));
		i++;
	}
	ft_vector_free(vector);
}

