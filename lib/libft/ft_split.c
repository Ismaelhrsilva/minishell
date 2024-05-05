/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:29:07 by ishenriq          #+#    #+#             */
/*   Updated: 2023/10/28 21:14:13 by ishenriq         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_n_blocks_array(const char *s, char c)
{
	int	i;
	int	j;
	int	count;
	int	len;

	i = 0;
	j = 0;
	count = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	if (count == 0)
		return (0);
	return (count);
}

static char	**create_split(char const *s, char c, char **ret_split)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	j = 0;
	w = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j = i;
			while (s[j] != c && s[j] != '\0')
				j++;
			ret_split[w] = ft_substr(s, i, j - i);
			w++;
			i = j;
		}
		if (s[i] != '\0')
			i++;
	}
	ret_split[w] = (char *) 0;
	return (ret_split);
}

char	**ft_split(char const *s, char c)
{
	char	**ret_split;
	int		count;

	if (ft_strlen(s) == 0)
		return (ft_calloc(1, sizeof(char *)));
	count = ft_n_blocks_array(s, c);
	if (count == 0)
		return (ft_calloc(1, sizeof(char *)));
	ret_split = ft_calloc(count + 1, sizeof(char *));
	if (ret_split == 0)
		return (ft_calloc(1, sizeof(char *)));
	ret_split = create_split(s, c, ret_split);
	return (ret_split);
}
