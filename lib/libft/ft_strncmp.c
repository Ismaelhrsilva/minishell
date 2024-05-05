/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:07:21 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/24 21:00:51 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *) s1;
	s4 = (unsigned char *) s2;
	while (*s3 != '\0' && *s4 != '\0' && n > 0)
	{
		if (*s3 != *s4)
			return (*s3 - *s4);
		n--;
		s3++;
		s4++;
	}
	if (n == 0)
		return (0);
	else
		return (*s3 - *s4);
}
