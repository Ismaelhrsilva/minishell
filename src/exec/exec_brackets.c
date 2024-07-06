/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_brackets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:28:52 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/06 17:11:49 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	ft_exec_brackets(t_node *root, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		status_here(FORK, 1);
		ft_to_execute(root->str, shell);
		ft_clear(shell);
		exit(ft_status(-1));
	}
	ft_pid_status(pid);
}
