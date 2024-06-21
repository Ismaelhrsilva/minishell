/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:10:42 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/20 21:16:17 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	ft_error(char *cmd, char *flag, char *msg, int status)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	if (status == ENOENT)
		g_status = 127;
	else
		g_status = status;
	ft_status(g_status);
}
