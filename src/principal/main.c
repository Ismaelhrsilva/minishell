/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/09 20:08:32 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

void	ft_return_terminal(int ret)
{
	static struct termios	term;

	if (!ret)
		tcgetattr(STDIN_FILENO, &term);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(void)
{
	t_shell		*shell;
	extern char	**environ;

	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	shell->envp = environ;
	shell->str = 0;
	ft_init_signal();
	ft_envp(shell);
	ft_status(0);
	ft_return_terminal(0);
	while (true)
	{
		ft_sigquit();
		ft_to_execute(read_line(), shell);
	}
	return (0);
}
