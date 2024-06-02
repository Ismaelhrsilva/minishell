/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/02 20:44:51 by ishenriq         ###   ########.fr       */
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
			/*if (ft_strncmp(parse->prompt, "export", 6) == 0)
			{
				int	i;
				int	j;
				char **ev;
				i = 0;
				while (i < shell->envp_dict->size)
				{
					ft_printf("%s=", ft_value(shell->envp_dict, i, 0));
					j = 0;
					ev = ft_value(shell->envp_dict, i, 1);
					while (j < ft_count_matrix(ev))
						ft_printf("%s:", ev[j++]);
					i++;
					ft_printf("\n");
				}
				continue ;
			}*/
			shell->prompt_splitted = ft_parser(parse);
			if (!shell->prompt_splitted)
				break ;
			parse->phrase = ft_construct_phrase(shell->prompt_splitted);
			ft_grammar_rules(parse->phrase);
			shell->root = ft_ast(parse->phrase);
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
