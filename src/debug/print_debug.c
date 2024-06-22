/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:07:15 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 20:58:02 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_vector_content(t_vector *phrase)
{
	int	i;

	i = 0;
	while (i < phrase->size)
	{
		ft_printf("----------------------------------------------\n");
		ft_printf("token: %s\n", ft_value(phrase, i, 0));
		ft_printf("token: %d\n", ft_value_int(phrase, i, 1));
		ft_printf("----------------------------------------------\n");
		i++;
	}
}

void	ft_print_ast(t_node	*root, char *branch)
{
	if (root)
	{
		if (root->left)
		{
			ft_print_ast(root->left, "left");
		}
		if (root->right)
		{
			ft_print_ast(root->right, "right");
		}
		ft_printf("%s ---> %s\n", branch, root->str);
	}
}
