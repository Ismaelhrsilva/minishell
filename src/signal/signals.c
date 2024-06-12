/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:26:39 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/12 19:14:11 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static void	ft_handle_sigint(int signal)
{
	g_status = signal;
	//ft_printf("sinal\n");
	if (status_here(HERE_DOC, -1))
	{
		close(STDIN_FILENO);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	if (status_here(PROMPT, -1))
		rl_redisplay();
}

void	ft_init_signal(void)
{
	if (signal(SIGINT, ft_handle_sigint) || 
	signal(SIGQUIT, SIG_IGN) )
		exit (0);
}
