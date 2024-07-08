/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:50:09 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/07 20:26:32 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_eliminate_ch_corner(char *str)
{
	int	size;
	int	i;

	size = ft_strlen(str);
	i = 0;
	while (i < size)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i - 1] = '\0';
	str[i - 2] = '\0';
}

void	ft_inside_ast(t_node *root)
{
	free(root->str);
	free(root->str_not_expanded);
	ft_freephrase(root->phrase);
}

/*void	ft_inside_ast(t_node *root)
{
	t_vector	*vector;
	size_t			i;

	vector = root->phrase;
	i = 0;
	//free(root->type);
	free(root->str);
	free(root->str_not_expanded);
	if (root->phrase)
		ft_freephrase_2(root->phrase);
	while (i < vector->size)
	{
		if (((t_vector *)vector->values[i])->values[0])
			free(((t_vector *)vector->values[i])->values[0]);
		free(vector->values[i]);
		i++;
	}
	free(vector);
}*/
