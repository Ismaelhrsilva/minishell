/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:13:19 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 18:20:52 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		ilen;

	i = 0;
	ilen = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *) big);
	if (len == 0)
		return (NULL);
	while (big[i] != '\0' && i + ilen <= len)
	{
		if (ft_strncmp(&big[i], little, ilen) == 0)
			return ((char *) &big[i]);
		else
			i++;
	}
	return (0);
}
