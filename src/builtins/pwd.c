/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:56 by paranha           #+#    #+#             */
/*   Updated: 2024/06/23 20:12:57 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	builtin_pwd(t_shell *shell, t_vector *cmd)
{
	char	cwd[PATH_MAX];

	(void)cmd;
	g_status = EXIT_SUCCESS;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
	{
		ft_putendl_fd("Error getting current directory", STDERR_FILENO);
		g_status = EXIT_FAILURE;
	}
}
