/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:31:38 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/30 15:10:09 by ishenriq         ###   ########.fr       */
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

static	void	ft_print_ast(t_node	*root, char *branch)
{
	if (root)
	{
		ft_printf("%s ---> %s\n", branch, root->str);
		ft_print_ast(root->left, "left");
		ft_print_ast(root->right, "right");
	}
}

t_node	*ft_ast_aux(t_phrase	*phrase, t_node *root, int size, int side)
{
	t_node *node;

	if (size == 0)
		return (t_node *) 0;
	node = ft_build_node(ft_pop_phrase(phrase));
	if (root == NULL)
	{
		root = node;
		ft_ast_aux(phrase, root, phrase->size, LEFT);
		return root;
	}
	if (node->type & OR_AND)
	{
		if (size == LEFT)
			node->left = root;
		else
			node->right = root;
		root = node;
		ft_ast_aux(phrase, root, phrase->size, !side);
		return root;
	}
	else
	{
		if (side)
			root->right = node;
		else
			root->left = node;
		ft_ast_aux(phrase, root, phrase->size, LEFT);
	}
}

static	t_node	*ft_ast_aux2(t_phrase *phrase, int start, int end, t_node *root)
{
	int	pos_token;
	t_node *node;

	pos_token = 0;
	if (start == end)
	{
		node = ft_build_node(ft_pop_phrase(phrase));
		return (node);
	}
	if (ft_pos_token_back(phrase, start, end, OR_AND) > 0)
	{	
		pos_token = ft_pos_token_back(phrase, start, end, OR_AND);
	}
	else if (ft_pos_token_back(phrase, start , end, PIPE) > 0)
	{
		pos_token = ft_pos_token_back(phrase, start, end, PIPE);
	}
	else if (ft_pos_token_back(phrase, start , end, REDALL) > 0)
	{
		pos_token = ft_pos_token_back(phrase, start, end, REDALL);
	}
	if (root == NULL)
	{
		root = ft_build_node(ft_pop_pos_phrase(phrase, pos_token));
		if (pos_token == 0)
		{
			//root->left = ft_ast_aux2(phrase, start, pos_token, node);
			root->right = ft_ast_aux2(phrase, 1, end, node);
		}
		else
		{
			root->left = ft_ast_aux2(phrase, start, pos_token, node);
			root->right = ft_ast_aux2(phrase, pos_token + 1, end, node);
		}
	}
	else
	{
		//node = ft_build_node(ft_pop_phrase(phrase));
		root->left = ft_ast_aux2(phrase, start + 1, end, node);
	}
	ft_printf("%d\n", phrase->size);
}

void	ft_ast(t_phrase *phrase, t_shell *shell)
{
	shell->root = ft_ast_aux2(phrase, 0, phrase->size, NULL);
	ft_print_ast(shell->root, "root");
}
