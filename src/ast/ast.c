/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:31:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/03 17:58:45 by ishenriq         ###   ########.fr       */
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

static int	ft_branch(t_vector *phrase, int pos, t_node *root)
{
	t_vector *right;
	int 	i;

	if (!phrase || pos < 0 || pos > phrase->size || !root)
		return (0);
	right = ft_vector_slice_right(phrase, pos);
	root->type = ft_value_int(phrase, pos, 1);
	root->str = ft_value(phrase, pos, 0);
	ft_vector_erase(phrase, pos);
	root->left = ft_ast(phrase);
	root->right = ft_ast(right);
	i = 0;
	/*while (i < phrase->size)
	{
		ft_printf("%s\n", ft_value(phrase, i, 0));
		i++;
	}
	ft_printf("-----------------------------------------\n");
	i = 0;
	while (i < right->size)
	{
		ft_printf("%s\n", ft_value(right, i, 0));
		i++;
	}
	//ft_printf("metacharacter - %d\n", root->type);*/
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
	i = phrase->size;
	/*while (i >= 0)
	{
		ft_printf("%s\n", ft_value(phrase, i, 0));
		i--;
	}*/
	root->type = EXEC;
	root->str = ft_value(phrase, 0, 0);
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
