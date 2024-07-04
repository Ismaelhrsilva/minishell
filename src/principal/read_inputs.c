/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/04 11:44:28 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	ft_to_execute(char *str, t_shell *shell)
{
	t_parse	*parse;
	char	**prompt_splitted;
	t_node	*root;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return ;
	if (!str)
		return ;
	parse->prompt = str;
	prompt_splitted = ft_parser(parse);
	parse->phrase = ft_construct_phrase(prompt_splitted, shell);
	parse->phrase_grammar = ft_construct_phrase(prompt_splitted, shell);
	ft_order_redall(parse->phrase);
	root = ft_ast(parse->phrase);
	ft_open_heredoc(root, shell);
	if (ft_grammar_rules(parse->phrase_grammar))
	{
		ft_execution(root, shell);
		free(root);
		parse->phrase = NULL;
		parse->phrase_grammar = NULL;
		root = NULL;
	}
	// ft_free_phrase(parse->phrase);
	// ft_free_phrase(parse->phrase_grammar);
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
		exit(255);
	add_history(prompt);
	return (prompt);
}
