/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:29:31 by ishenriq          #+#    #+#             */
/*   Updated: 2023/11/04 17:02:37 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	total_size;

	p = 0;
	total_size = nmemb * size;
	if (!nmemb || !size || nmemb == total_size / size)
		p = malloc(nmemb * size);
	if (p == 0)
		return (p);
	ft_bzero(p, nmemb * size);
	return (p);
}
