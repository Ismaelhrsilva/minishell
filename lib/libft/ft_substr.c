/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:47:02 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/02 19:20:18 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	end;
	int				i;

	i = 0;
	end = len + start;
	if (start > ft_strlen(s))
	{
		substr = (char *)ft_calloc(1, sizeof(char));
		substr[0] = '\0';
		return (substr);
	}
	if (len > ft_strlen(s) - start)
		substr = (char *)ft_calloc(ft_strlen(s) - start + 1, sizeof(char));
	else
		substr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (0);
	while (start < end && s[start] != '\0')
		substr[i++] = s[start++];
	return (substr);
}
