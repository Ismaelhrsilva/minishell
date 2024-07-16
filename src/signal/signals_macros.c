/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_macros.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:20 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/12 16:32:51 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_term_by_signal(int status)
{
	return (((signed char)((status & 0x7f) + 1) >> 1) > 0);
}

int	ft_term_normaly(int status)
{
	return (ft_term_by_signal(status) == 0);
}

int	ft_exit_status(int status)
{
	return ((status >> 8) & 0xFF);
}

int	ft_term_signal(int status)
{
	return (status & 0x7F);
}

int	ft_get_return_value(int status)
{
	if (ft_term_by_signal(status))
		return (ft_term_signal(status) + 128);
	return (ft_exit_status(status));
}
