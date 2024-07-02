/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:12:04 by paranha           #+#    #+#             */
/*   Updated: 2024/07/02 15:37:56 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_builtin_echo(t_shell *shell, t_vector *cmd)
//{
//	size_t	i;
//	int	no_newline;
//
//	(void)shell;
//	ft_status(0);
//	i = 1;
//	no_newline = 0;
//	if (ft_value(cmd, 1, 0) && ft_strcmp(ft_value(cmd, 1, 0), "-n") == 0)
//		no_newline = 1;
//	while (i + no_newline < cmd->size)
//	{
//		if (i > 1)
//			ft_putchar_fd(' ', STDOUT_FILENO);
//		ft_putstr_fd(ft_value(cmd, i + no_newline, 0), STDOUT_FILENO);
//		i++;
//	}
//	if (!no_newline)
//		ft_putchar_fd('\n', STDOUT_FILENO);
//}

// void	ft_builtin_echo(t_shell *shell, t_vector *cmd)
//{
//	size_t	i;
//	int		no_newline;
//
//	(void)shell;
//	ft_status(0);
//	i = 1;
//	no_newline = 0;
//	while (i < cmd->size && ((char *)ft_value(cmd, i, 0))[0] == '-')
//	{
//		size_t j = 1;
//		int valid_flag = 1;
//
//		while (((char *)ft_value(cmd, i, 0))[j])
//		{
//			if (((char *)ft_value(cmd, i, 0))[j] != 'n')
//			{
//				valid_flag = 0;
//				break ;
//			}
//			j++;
//		}
//		if (!valid_flag)
//			break ;
//		no_newline = 1;
//		i++;
//	}
//	int first_arg = 1;
//	while (i < cmd->size)
//	{
//		if (!first_arg)
//			ft_putchar_fd(' ', STDOUT_FILENO);
//		ft_putstr_fd((char *)ft_value(cmd, i, 0), STDOUT_FILENO);
//		first_arg = 0;
//		i++;
//	}
//	if (!no_newline)
//		ft_putchar_fd('\n', STDOUT_FILENO);
//}

// int	handle_flags(t_vector *cmd, size_t *index)
//{
//	size_t	i;
//	int		no_newline;
//
//	i = 1;
//	no_newline = 0;
//	while (i < cmd->size && ((char *)ft_value(cmd, i, 0))[0] == '-')
//	{
//		size_t j = 1;
//		int valid_flag = 1;
//
//		while (((char *)ft_value(cmd, i, 0))[j])
//		{
//			if (!strchr("n", ((char *)ft_value(cmd, i, 0))[j]))
//			{
//				valid_flag = 0;
//				break ;
//			}
//			j++;
//		}
//		if (!valid_flag)
//			break ;
//		no_newline = 1;
//		i++;
//	}
//	*index = i;
//	return (no_newline);
//}
//
// void	ft_builtin_echo(t_shell *shell, t_vector *cmd)
//{
//	size_t	i;
//	int		no_newline;
//	int		first_arg;
//
//	(void)shell;
//	ft_status(0);
//	no_newline = handle_flags(cmd, &i);
//	first_arg = 1;
//	while (i < cmd->size)
//	{
//		if (!first_arg)
//			ft_putchar_fd(' ', STDOUT_FILENO);
//		ft_putstr_fd((char *)ft_value(cmd, i, 0), STDOUT_FILENO);
//		first_arg = 0;
//		i++;
//	}
//	if (!no_newline)
//		ft_putchar_fd('\n', STDOUT_FILENO);
//}

int	handle_flags(t_vector *cmd, size_t *index, size_t i, size_t j)
{
	int		no_newline;
	int		valid_flag;

	no_newline = 0;
	while (i < cmd->size && ((char *)ft_value(cmd, i, 0))[0] == '-')
	{
		valid_flag = 1;
		while (((char *)ft_value(cmd, i, 0))[j])
		{
			if (!strchr("n", ((char *)ft_value(cmd, i, 0))[j]))
			{
				valid_flag = 0;
				break ;
			}
			j++;
		}
		if (!valid_flag)
			break ;
		no_newline = 1;
		i++;
	}
	*index = i;
	return (no_newline);
}

void	ft_builtin_echo(t_shell *shell, t_vector *cmd)
{
	size_t	i;
	int		no_newline;
	int		first_arg;

	(void)shell;
	ft_status(0);
	no_newline = handle_flags(cmd, &i, 1, 1);
	first_arg = 1;
	while (i < cmd->size)
	{
		if (!first_arg)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd((char *)ft_value(cmd, i, 0), STDOUT_FILENO);
		first_arg = 0;
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
