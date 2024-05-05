/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:54:53 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 18:26:34 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	c = (unsigned char ) c;
	len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (c == '\0')
		return ((char *)s + len);
	while (--len >= 0)
	{
		if (*(s + len) == c)
			return ((char *) s + len);
	}
	return (NULL);
}
