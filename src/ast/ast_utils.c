/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:50:09 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 20:33:45 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_eliminate_ch_corner(char *str)
{
	int	size;
	int	i;

	size = ft_strlen(str);
	i = 0;
	while (i < size)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i - 1] = '\0';
	str[i - 2] = '\0';
}
