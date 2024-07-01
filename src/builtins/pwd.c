/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:56 by paranha           #+#    #+#             */
/*   Updated: 2024/07/01 18:03:20 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_pwd(t_shell *shell, t_vector *cmd)
{
	char	cwd[PATH_MAX];

	(void)cmd;
	ft_status(0);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
	{
		ft_putendl_fd("Error getting current directory", STDERR_FILENO);
		ft_status(1);
	}
}
