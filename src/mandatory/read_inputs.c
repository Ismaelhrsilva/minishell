/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/10 22:33:32 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

void	read_line(s_parse *parse)
{
	while (1)
	{
		parse->prompt = readline("minishell>$ ");
		if (parse->prompt != NULL)
		{
			add_history(parse->prompt);
			ft_parser(parse);
			if (!ft_strncmp(parse->prompt, "exit", 4))
				break ;
		}
	}
}
