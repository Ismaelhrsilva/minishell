/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:26:53 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 21:12:34 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	b;

	p = (unsigned char *) s;
	b = (unsigned char) c;
	while (n--)
	{
		if (*p != b)
			p++;
		else
			return (p);
	}
	return (0);
}
