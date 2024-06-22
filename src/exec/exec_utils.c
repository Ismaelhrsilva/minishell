/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:26:34 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 20:39:38 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

int	ft_status(int st)
{
	static int	status;

	if (st != -1)
		status = st;
	return (status);
}

void	close_fd(int *fd)
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

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	g_status = status;
	ft_status(g_status);
}
