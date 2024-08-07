/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:26:39 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/06 16:15:44 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static void	ft_handle_sigint(int signal)
{
	g_status = signal;
	if (status_here(FORK, -1))
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	if (status_here(HERE_DOC, -1))
		close(STDIN_FILENO);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (!status_here(PROMPT, -1))
		rl_redisplay();
}

static t_status	*ft_init_status(void)
{
	static t_status	status;

	return (&status);
}

int	status_here(int where, int st)
{
	t_status	*status;

	status = ft_init_status();
	if (where == 0)
	{
		if (st != -1)
			status->_heredoc = st;
		return (status->_heredoc);
	}
	else if (where == 1)
	{
		if (st == 1)
			status->_fork = st;
		return (status->_fork);
	}
	else if (where == 2)
	{
		if (st != -1)
			status->_prompt = st;
		return (status->_prompt);
	}
	else
		return (-2);
}

void	ft_sigquit(void)
{
	if (g_status == 131)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		ft_return_terminal(1);
	}
	ft_return_terminal(0);
}

void	ft_init_signal(void)
{
	if (signal(SIGINT, ft_handle_sigint)
		|| signal(SIGQUIT, SIG_IGN))
		exit (0);
}
