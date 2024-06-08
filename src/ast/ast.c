/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:31:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/08 20:02:27 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_node	*ft_build_node(t_vector *word)
{
	t_node	*node;

	if (!word)
		return ((t_node *)0);
	node = malloc(sizeof(t_node));
	if (!node)
		return ((t_node *)0);
	node->str = ft_value(word, 0, 0);
	node->type = ft_value_int(word, 0, 1);
	node->left = NULL;
	node->right = NULL;
	node->phrase = NULL;
	return (node);
}

static int	ft_branch(t_vector *phrase, int pos, t_node *root)
{
	t_vector *right;

	if (!phrase || pos < 0 || pos > phrase->size || !root)
		return (0);
	right = ft_vector_slice_right(phrase, pos);
	root->type = ft_value_int(phrase, pos, 1);
	root->str = ft_value(phrase, pos, 0);
	root->fd = 0;
	ft_vector_erase(phrase, pos);
	root->left = ft_ast(phrase);
	root->right = ft_ast(right);
	//ft_print_vector_content(phrase);
	//printf("------------------------\n");
	//ft_print_vector_content(right);
	return (1);
}

static	void	ft_ast_aux(t_vector *phrase, t_node *root)
{
	if (ft_branch(phrase, ft_pos_token_back(phrase, OR_AND), root))
		return ;
	if (ft_branch(phrase, ft_pos_token_back(phrase, PIPE), root))
		return ;
	if (ft_branch(phrase, ft_pos_token_back(phrase, REDALL), root))
		return ;
	root->str = ft_value(phrase, 0, 0);
	if (root->str && root->str[0] == '(')
	{
		ft_eliminate_brackets(root->str);
	}
	root->type = EXEC;
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
