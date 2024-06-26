/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:42 by paranha           #+#    #+#             */
/*   Updated: 2024/06/26 17:33:31 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

static int	check_arg(const char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i])
		return (0);
	return (1);
}


void	builtin_exit(t_shell *shell, t_vector *cmd)
{
	int				i;
	unsigned char	exit_status;
	char			*arg;

	exit_status = 0;
	i = 1;
	while (i < cmd->size)
	{
		arg = ft_value(cmd, i, 0);
		if (check_arg(arg))
		{
			exit_status = (unsigned char)ft_atoi(arg);
			break ;
		}
		i++;
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (i > 1 && ft_value(cmd, 1, 0)
		&& !check_arg(ft_value(cmd, 1, 0)))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(2);
	}
	else if (ft_value(cmd, 1, 0) && ft_value(cmd, 2, 0))
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		ft_status(1);
		//g_status = EXIT_FAILURE;
		return ;
	}
	exit(exit_status);
}
