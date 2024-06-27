/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phraranha <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:18:51 by phraranha         #+#    #+#             */
/*   Updated: 2024/06/27 17:20:36 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freesplit(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_getenv(t_vector *env, char *name)
{
	unsigned long	i;
	t_vector		*line;
	char			*identifier;
	char			*value;

	i = 0;
	if (!env || !name)
		return (NULL);
	while (i < ft_vector_size(env))
	{
		line = ft_vector_at(env, i);
		if (!line || ft_vector_size(line) < 2)
		{
			i++;
			continue ;
		}
		identifier = ft_vector_at(line, 0);
		value = ft_vector_at(line, 1);
		if (identifier && ft_strcmp(identifier, name) == 0)
			return ((char *)value);
		i++;
	}
	return (NULL);
}
