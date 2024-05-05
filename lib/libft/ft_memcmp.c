/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:58:14 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/28 19:23:40 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*t1 != *t2)
		{
			if (*t1 > *t2)
				return (1);
			else
				return (-1);
		}
		n--;
		t1++;
		t2++;
	}
	return (0);
}
