/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/07 18:27:44 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

// void	ft_to_execute(char *str, t_shell *shell)
//{
//	t_parse	*parse;
//	char	**prompt_splitted;
//	t_node	*root;
//
//	parse = malloc(sizeof(t_parse));
//	if (!parse)
//		return ;
//	if (!str)
//		return ;
//	parse->prompt = str;
//	prompt_splitted = ft_parser(parse);
//	parse->phrase = ft_construct_phrase(prompt_splitted, shell);
//	parse->phrase_grammar = ft_construct_phrase(prompt_splitted, shell);
//	ft_order_redall(parse->phrase);
//	root = ft_ast(parse->phrase);
//	ft_open_heredoc(root, shell);
//	if (ft_grammar_rules(parse->phrase_grammar))
//	{
//		ft_execution(root, shell);
//		free(root);
//		parse->phrase = NULL;
//		parse->phrase_grammar = NULL;
//		root = NULL;
//	}
//	ft_free_parse(parse);
//	return ;
//}

void	ft_free_root(t_node *root)
{
	if (root->left)
		ft_free_root(root->left);
	if (root->right)
		ft_free_root(root->right);
	if (root->phrase)
		ft_vector_free(root->phrase);
	free(root);
}

void	ft_free_parse(t_parse *parse)
{
//	if (parse->phrase)
//		ft_free_phrase(parse->phrase);
//	if (parse->phrase_grammar)
//		ft_free_phrase(parse->phrase_grammar);
	free(parse);
}

/*void	ft_freephrase(t_vector *vector)
{
	size_t	i;

	i = 0;
	while (i < vector->size)
	{
		free(vector->values[0]);
		free(vector->values[1]);
		free(vector->values[2]);
		i++;
	}
	free(vector);
}*/

/*void	ft_freephrase(t_vector *vector)
{
	size_t	i;
	size_t	j;
	//t_vector *temp;

	i = 0;
	while (i < vector->size)
	{

		j = 0;
		while (j < 3)
		{
			temp = ((t_vector *)vector->values[i])->values[j];
			if (temp)
				temp->values = NULL;
				//free(temp->values);
			j++;
		}
		ft_vector_shrink_to_fit(((t_vector *)vector)->values[i]);
		free(((t_vector *)vector->values[i])->values[0]);
		free(((t_vector *)vector->values[i])->values[1]);
		free(((t_vector *)vector->values[i])->values[2]);
		i++;
	}
	i = 0;
	ft_vector_shrink_to_fit(vector);
	while (i < vector->size)
	{
		free(((t_vector *)vector->values[i])->values);
		i++;
	}
	i = 0;
	while (i < vector->size)
	{
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
}*/

void	ft_freephrase(t_vector *vector)
{
	size_t	i;

	i = 0;
	while (i < vector->size)
	{
		free(((t_vector *)vector->values[i])->values[0]);
		free(((t_vector *)vector->values[i])->values[1]);
		free(((t_vector *)vector->values[i])->values[2]);
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
	while (i < vector->size)
	{
		free(((t_vector *)vector->values[i])->values[0]);
		//free(((t_vector *)vector->values[i])->values[1]);
		free(((t_vector *)vector->values[i])->values);
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
}

void	ft_to_execute(char *str, t_shell *shell)
{
	t_parse	*parse;
	t_node	*root;

	if (!str)
		return ;
	parse = malloc(sizeof(t_parse));
	if (!parse)
		return ;
	shell->parse = parse;
	parse->prompt = str;
	parse->prompt_splitted = ft_parser(parse);
	parse->phrase = ft_construct_phrase(parse->prompt_splitted, shell);
	parse->phrase_grammar = ft_construct_phrase(parse->prompt_splitted, shell);
	if (parse->phrase)
		ft_order_redall(parse->phrase);
	root = ft_ast(parse->phrase);
	if (root)
	{
		ft_open_heredoc(root, shell);
		shell->root = root;
		if (ft_grammar_rules(parse->phrase_grammar))
		{
			ft_freephrase(parse->phrase_grammar);
			ft_execution(root, shell);
		}
		ft_clear_ast(root);
		root = NULL;
	}
	ft_free_matrix(shell->parse->prompt_splitted);
	ft_free_parse(parse);
	return ;
}

// void	ft_to_execute(char *str, t_shell *shell)
//{
//    t_parse	*parse;
//    char	**prompt_splitted;
//    t_node	*root;
//
//    parse = malloc(sizeof(t_parse));
//    if (!parse || !str)
//        return ;
//    parse->prompt = str;
//    prompt_splitted = ft_parser(parse);
//    parse->phrase = ft_construct_phrase(prompt_splitted, shell);
//    parse->phrase_grammar = ft_construct_phrase(prompt_splitted, shell);
//    ft_order_redall(parse->phrase);
//    root = ft_ast(parse->phrase);
//    ft_open_heredoc(root, shell);
//    if (ft_grammar_rules(parse->phrase_grammar))
//    {
//        ft_execution(root, shell);
//        free(root);
//        parse->phrase = NULL;
//        parse->phrase_grammar = NULL;
//        root = NULL;
//    }
//    ft_free_phrase(parse->phrase);
//    ft_free_phrase(parse->phrase_grammar);
//    free(parse);
//    return ;
//}

char	*read_line(void)
{
	char	*prompt;

	status_here(PROMPT, 0);
	prompt = readline("minishell>$ ");
	status_here(PROMPT, 1);
	if (!prompt)
		exit(0);
	add_history(prompt);
	return (prompt);
}
