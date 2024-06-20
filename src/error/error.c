/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:10:42 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/20 18:25:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg, int g_status)
{
	ft_putstr_fd("minishell: failed to:", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(g_status);
}
