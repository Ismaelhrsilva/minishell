/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:42 by paranha           #+#    #+#             */
/*   Updated: 2024/06/27 20:15:24 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

unsigned char	parse_exit_arguments(t_vector *cmd)
{
	int				i;
	char			*arg;
	unsigned char	exit_status;

	i = 1;
	exit_status = 0;
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
	return (exit_status);
}

void	builtin_exit(t_shell *shell, t_vector *cmd)
{
	unsigned char	exit_status;

	exit_status = parse_exit_arguments(cmd);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->size > 1 && !check_arg(ft_value(cmd, 1, 0)))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(2);
	}
	else if (cmd->size > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		ft_status(1);
		return ;
	}
	ft_clear(shell);
	exit(exit_status);
}
