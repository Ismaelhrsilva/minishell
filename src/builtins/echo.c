/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:04 by paranha           #+#    #+#             */
/*   Updated: 2024/06/29 19:30:06 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	ft_builtin_echo(t_shell *shell, t_vector *cmd)
{
	int	i;
	int	no_newline;

	g_status = EXIT_SUCCESS;
	(void)shell;
	i = 1;
	no_newline = 0;
	if (ft_value(cmd, 1, 0) && ft_strcmp(ft_value(cmd, 1, 0), "-n") == 0)
		no_newline = 1;
	while (i + no_newline < cmd->size)
	{
		if (i > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(ft_value(cmd, i + no_newline, 0), STDOUT_FILENO);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
