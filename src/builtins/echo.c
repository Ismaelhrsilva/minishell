/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:04 by paranha           #+#    #+#             */
/*   Updated: 2024/06/23 20:12:05 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	builtin_echo(t_shell *shell, t_vector *cmd)
{
	int	i;
	int	no_newline;

	g_status = EXIT_SUCCESS;
	(void)shell;
	i = 1;
	no_newline = 0;
	if (cmd->values[1] && ft_strcmp(((t_vector *)cmd->values[1])->values[0],
			"-n") == 0)
		no_newline = 1;
	while (i + no_newline < cmd->size)
	{
		if (i > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(((t_vector *)cmd->values[i + no_newline])->values[0],
			STDOUT_FILENO);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
