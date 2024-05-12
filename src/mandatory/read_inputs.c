/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/12 19:24:43 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

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
			if (!ft_strncmp(parse->prompt, "exit", 4))
				break ;
		}
	}
}
