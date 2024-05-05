/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:29:07 by ishenriq          #+#    #+#             */
/*   Updated: 2024/03/08 12:58:17 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_strrplc_split(char **splitted, char *tmp)
{
	int	i;

	splitted = ft_split(tmp, ' ');
	i = 0;
	while (splitted[i])
		ft_strrplc(splitted[i++], 0x1A, ' ');
	return (splitted);
}

char	**ft_split_quote(char *tmp)
{
	int		i;
	char	sign;
	char	**splitted;

	i = -1;
	sign = 0;
	splitted = NULL;
	while (tmp && *(tmp + ++i))
	{
		if (sign && *(tmp + i) == sign)
		{
			*(tmp + i) = ' ';
			sign = 0;
		}
		else if (!sign && (*(tmp + i) == '\"' || *(tmp + i) == '\''))
		{
			sign = *(tmp + i);
			*(tmp + i) = ' ';
		}
		else if (sign && *(tmp + i) == ' ')
			*(tmp + i) = 0x1A;
	}
	splitted = ft_strrplc_split(splitted, tmp);
	return (splitted);
}
