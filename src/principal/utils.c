/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:57:08 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/30 17:10:43 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_power(int nb, int power)
{
	int	result;

	result = 1;
	if (nb > 0 && power > 0)
		while (power-- > 0)
			result *= nb;
	return (result);
}

int	ft_count_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_change_sub_space(char **split)
{
	int		j;
	int		m;

	m = 0;
	j = 0;
	while (split[m])
	{
		while (split[m][j])
		{
			if (split[m][j] == 0x1A)
				split[m][j] = ' ';
			j++;
		}
		m++;
	}
}
