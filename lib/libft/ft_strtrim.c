/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:44:09 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/30 18:22:02 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	count;

	count = 0;
	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
		return (ft_substr(s1, 0, ft_strlen(s1)));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[i]))
	{
		i--;
		count++;
	}
	return (ft_substr(s1, 0, ft_strlen(s1) - count + 1));
}
