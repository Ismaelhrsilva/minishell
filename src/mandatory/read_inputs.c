/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/05 16:45:12 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

void	read_line(s_minishell *minishell)
{
	while (1)
	{
		minishell->argv = readline("minishell>$ ");
		if (minishell->argv != NULL)
		{
			add_history(minishell->argv);
			ft_parser(minishell);
			if (!ft_strncmp(minishell->argv, "exit", 4))
				break ;
		}
	}
}
