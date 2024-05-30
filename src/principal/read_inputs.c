/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/30 17:10:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(t_shell *shell)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (parse == NULL)
		return ;
	while (1)
	{
		parse->prompt = readline("minishell>$ ");
		if (parse->prompt != NULL)
		{
			add_history(parse->prompt);
			shell->prompt_splitted = ft_parser(parse);
			parse->phrase = ft_construct_phrase(shell->prompt_splitted);
			ft_grammar_rules(parse->phrase);
			//ft_ast(parse->phrase, shell);
			if (!ft_strncmp(parse->prompt, "exit", 4))
				break ;
		}
	}
}
