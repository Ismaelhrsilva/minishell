/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:33:02 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 21:19:26 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (ret == NULL)
		return (0);
	else
	{
		while (s[i])
		{
			ret[i] = f(i, s[i]);
			i++;
		}
	}
	return (ret);
}
