/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/05 15:35:50 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static void	read_line(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("minishell>$ ");
		if (prompt != NULL)
		{
			add_history(prompt);
			if (!ft_strncmp(prompt, "exit", 4))
			{
				free(prompt);
				break ;
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	read_line();
	return (0);
}
