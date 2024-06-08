/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:26:34 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/07 22:59:24 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

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

