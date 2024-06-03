/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:31:31 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/03 18:31:12 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_pathname(char **matrix, char *str)
{
	char	*bar;
	char	*pathname;
	int	i;

	while (matrix[i] != NULL)
	{
		bar = ft_strjoin(matrix[i], "/");
		pathname = ft_strjoin(bar, )
	}
}
