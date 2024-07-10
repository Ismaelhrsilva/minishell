/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:34:50 by paranha           #+#    #+#             */
/*   Updated: 2024/07/10 17:28:16 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_arg(char *arg)
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

static int	ft_is_number(char *str)
{
	const size_t	exit_limit = ft_strlen(MAX_EXIT);
	int				i;
	size_t			len;

	if (!ft_check_arg(str))
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	len = ft_strlen(&str[i]);
	if (len < exit_limit)
		return (1);
	if (len > exit_limit)
		return (0);
	if (str[0] == '-')
		return (ft_strcmp(&MIN_EXIT[1], &str[i]) >= 0);
	return (ft_strcmp(&str[i], MAX_EXIT) <= 0);
}

unsigned char	ft_parse_exit_arguments(t_vector *cmd)
{
	size_t			i;
	char			*arg;
	unsigned char	exit_status;

	i = 1;
	exit_status = 0;
	while (i < cmd->size)
	{
		arg = ft_value(cmd, i, 0);
		if (ft_is_number(arg))
		{
			exit_status = (unsigned char)ft_atoi(arg);
			break ;
		}
		i++;
	}
	return (exit_status);
}

void	ft_clear2(t_shell *shell)
{
	close_open_fds();
	ft_clear_ast(shell->root);
	ft_free_matrix(shell->parse->prompt_splitted);
	free(shell->parse);
	ft_free_shell(shell);
}

void	ft_builtin_exit(t_shell *shell, t_vector *cmd)
{
	unsigned char	exit_status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->size > 1 && !ft_is_number(ft_value(cmd, 1, 0)))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		ft_status(2);
		ft_clear2(shell);
		exit(2);
	}
	else if (cmd->size > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		ft_status(1);
		return ;
	}
	exit_status = ft_parse_exit_arguments(cmd);
	ft_clear2(shell);
	exit(exit_status);
}
