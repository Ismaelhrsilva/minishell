/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/05 18:58:13 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

void	read_line(s_minishell *minishell)
{
	while (1)
	{
		minishell->prompt = readline("minishell>$ ");
		if (minishell->prompt != NULL)
		{
			add_history(minishell->prompt);
			ft_parser(minishell);
			if (!ft_strncmp(minishell->prompt, "exit", 4))
				break ;
		}
	}
}
