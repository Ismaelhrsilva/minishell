/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_macros.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:07:20 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/06 16:12:51 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	term_by_signal(int status)
{
	return (((signed char)((status & 0x7f) + 1) >> 1) > 0);
}

int	term_normaly(int status)
{
	return (term_by_signal(status) == 0);
}

int	exit_status(int status)
{
	return ((status >> 8) & 0xFF);
}

int	term_signal(int status)
{
	return (status & 0x7F);
}

int	get_return_value(int status)
{
	if (term_by_signal(status))
		return (term_signal(status) + 128);
	return (exit_status(status));
}
