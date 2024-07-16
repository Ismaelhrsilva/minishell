/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:26:34 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/16 19:00:13 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_status(int st)
{
	static int	status;

	if (st != -1)
		status = st;
	return (status);
}

void	ft_close_fd(int *fd)
{
	if (!fd)
		return ;
	if (fd[0] > -1)
		close(fd[0]);
	if (fd[1] > -1)
		close(fd[1]);
}

void	ft_change_fds(int fd, int new)
{
	if (fd != -1)
	{
		dup2(fd, new);
		close(fd);
	}
}

void	ft_pid_status(pid_t pid)
{
	int	status;

	status = ft_status(-1);
	waitpid(pid, &status, WUNTRACED);
	status = ft_get_return_value(status);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	ft_status(status);
}

void	ft_pid_status_without_flobal(pid_t pid)
{
	int	status;

	status = ft_status(-1);
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	ft_status(status);
}
