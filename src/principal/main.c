/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/20 19:09:05 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	extern char	**environ;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	shell->envp = envp;
	ft_init_signal();
	ft_envp(shell);
	ft_status(0);
	while (true)
	{
		ft_sigquit();
		//g_status = 0;
		ft_to_execute(read_line(), shell);
	}
	return (0);
}
