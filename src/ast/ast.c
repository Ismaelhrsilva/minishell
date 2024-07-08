/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:31:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/07 21:08:52 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_branch(t_vector *phrase, long pos, t_node *root)
{
	t_vector	*right;

	if (!phrase || pos < 0 || pos > (long)phrase->size || !root)
		return (0);
	right = ft_vector_slice_right(phrase, pos);
	root->type = ft_value_int(phrase, pos, 1);
	root->str = ft_strdup(ft_value(phrase, pos, 0));
	root->fd = 0;
	free(((t_vector *)phrase->values[pos])->values[0]);
	free(((t_vector *)phrase->values[pos])->values[1]);
	free(((t_vector *)phrase->values[pos])->values[2]);
	free(((t_vector *)phrase->values[pos])->values);
	free(phrase->values[pos]);
	ft_vector_erase(phrase, pos);
	if (phrase->size > 0)
		root->left = ft_ast(phrase);
	if (right->size > 0)
		root->right = ft_ast(right);
	return (1);
}

static	void	ft_ast_aux(t_vector *phrase, t_node *root)
{
	if (phrase->size <= 0 || !root)
		return ;
	if (ft_branch(phrase, ft_pos_token_back(phrase, OR_AND), root))
		return ;
	if (ft_branch(phrase, ft_pos_token_back(phrase, PIPE), root))
		return ;
	if (ft_branch(phrase, ft_pos_token_back(phrase, REDALL), root))
		return ;
	root->str = ft_strdup(ft_value(phrase, 0, 0));
	root->str_not_expanded = ft_strdup(ft_value(phrase, 0, 2));
	root->type = ft_value_int(phrase, 0, 1);
	//root->type = EXEC;
	root->phrase = phrase;
}

t_node	*ft_ast(t_vector *phrase)
{
	t_node	*root;

	root = ft_calloc(1, sizeof(t_node));
	if (!root)
		return ((t_node *)0);
	ft_ast_aux(phrase, root);
	return (root);
}
