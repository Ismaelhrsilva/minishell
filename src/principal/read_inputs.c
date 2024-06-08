/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/08 16:47:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(t_shell *shell)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return ;
	while (1)
	{
		parse->prompt = readline("minishell>$ ");
		if (!parse->prompt)
			break ;
		if (parse->prompt != NULL)
		{
			add_history(parse->prompt);
			shell->prompt_splitted = ft_parser(parse);
			if (!shell->prompt_splitted)
				break ;
			parse->phrase = ft_construct_phrase(shell->prompt_splitted);
			ft_grammar_rules(parse->phrase);
			ft_order_redall(parse->phrase);
			ft_print_vector_content(parse->phrase);
			shell->root = ft_ast(parse->phrase);
			ft_open_heredoc(shell->root);
			//ft_execution(shell->root, shell);
			ft_print_ast(shell->root, "root");
			free(shell->root);
			parse->phrase = NULL;
			shell->root = NULL;
			if (!ft_strncmp(parse->prompt, "exit", 4))
				break ;
			ft_free_phrase(parse->phrase);
		}
		free(parse->prompt);
	}
	free(parse);
}
