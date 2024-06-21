/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:10:42 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 19:12:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

extern volatile sig_atomic_t	g_status;

void	ft_error(char *cmd, char *flag, char *msg, int status)
{
	struct stat	path_stat;

	path_stat = (struct stat){0};
	stat((const char *) cmd, &path_stat);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (flag)
	{
		ft_putstr_fd(flag, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if ((ft_strchr("./", cmd[0]) || cmd[ft_strlen(cmd) - 1] == '/')
		&& status != ENOENT && path_stat.st_mode & S_IFDIR)
		ft_putstr_fd("Is a directory", STDERR_FILENO);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	if (status == EACCES)
		g_status = 126;
	else if (status == ENOENT)
		g_status = 127;
	else
		g_status = status;
	ft_status(g_status);
}