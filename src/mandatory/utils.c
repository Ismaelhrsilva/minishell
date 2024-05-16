/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:57:08 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/15 20:01:58 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

int	ft_power(int nb, int power)
{
	int	result;

	result = 1;
	if (nb > 0 && power > 0)
		while (power-- > 0)
			result *= nb;
	return (result);
}
