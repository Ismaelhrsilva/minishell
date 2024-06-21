/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:31:31 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/21 20:21:31 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_cmd(char *str)
{
	if (str && ft_strncmp(str, "/", 1) == 0)
		if (access(str, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

char	*ft_get_pathname(char **matrix, char *str)
{
	char	*bar;
	char	*pathname;
	int	i;

	i = 0;
	if (ft_is_cmd(str))
		return (str);
	while (matrix[i] != NULL)
	{
		bar = ft_strjoin(matrix[i], "/");
		pathname = ft_strjoin(bar, str);
		if (pathname && access(pathname, F_OK | X_OK) == 0)
		{
			free(bar);
			return (pathname);
		}
		else 
		{
			free(bar);
			free (pathname);
		}
		i++;
	}
	return (str);
}

