/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:42:53 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/11 20:14:52 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

static t_status	*ft_init_status(void)
{
	static t_status	status;
	
	return (&status);
}

int	status_here(int where, int st)
{
	t_status *status;

	status = ft_init_status();
	if (where == 0)
		if (status->_heredoc != -1)
			status->_heredoc = st;
		else
			return (status->_heredoc);
	else if (where == 1)
		if (status->_fork != -1)
			status->_fork = st;
		else
			return (status->_fork);
	else if (where == 2)
		if (status->_prompt != -1)
			status->_prompt = st;
		else
			return (status->_prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	ft_init_signal();
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	shell->envp = envp;
	ft_envp(shell);
	while (true)
		ft_to_execute(read_line(), shell);
	return (0);
}
