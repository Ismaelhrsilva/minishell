/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:34:06 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/03 18:39:31 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrplc(char *str, char old, char new)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == old)
			*(str + i) = new;
		i++;
	}
}
