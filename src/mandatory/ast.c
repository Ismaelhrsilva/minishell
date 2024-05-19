/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:31:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/19 16:04:13 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static	t_node	*ft_build_node(t_word *word)
{
	t_node	*node;

	if (!word)
		return ((t_node *)0);
	node = malloc(sizeof(t_node));
	if (!node)
		return ((t_node *)0);
	node->str = word->word;
	node->type = word->token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}


void	ft_ast(t_phrase	*phrase)
{
	int	i;
	t_node *node_1;
	t_node *node_2;
	t_node *node_3;
	//t_word	*word;

	i = 0;
	//word = ft_pop_phrase(phrase);
	//while (i < phrase->size)
	//{
		
		//node_1 = ft_build_node(word);
		node_1 = ft_build_node(ft_pop_phrase(phrase));
		node_2 = ft_build_node(ft_pop_phrase(phrase));
		node_3 = ft_build_node(ft_pop_phrase(phrase));
		i++;
	//}
}
