/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:42 by paranha           #+#    #+#             */
/*   Updated: 2024/06/23 20:12:44 by paranha          ###   ########.org.br   */
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
	t_vector		*word;
	char			*arg;

	i = 0;
	exit_status = 0;
	while (cmd->values[++i])
	{
		word = (t_vector *)cmd->values[i];
		arg = (char *)word->values[0];
		if (check_arg(arg))
		{
			exit_status = (unsigned char)ft_atoi(arg);
			break ;
		}
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (i > 1 && cmd->values[1]
		&& !check_arg((char *)((t_vector *)cmd->values[1])->values[0]))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(2);
	}
	else if (cmd->values[1] && cmd->values[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		return ;
	}
	exit(exit_status);
}
