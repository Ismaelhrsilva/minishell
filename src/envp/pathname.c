/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:31:31 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/06 21:50:46 by paranha          ###   ########.org.br   */
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

char	*ft_get_pathname(char **matrix, char *str, int i)
{
	char	*bar;
	char	*pathname;

	if (ft_strlen(str) == 0 || matrix == NULL)
		return ("");
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
