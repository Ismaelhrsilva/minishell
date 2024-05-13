/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenazer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:18:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/13 19:40:04 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static char	*ft_token_before(int n)
{
	char	**token_before;

	token_before = malloc(6 * sizeof(char **));
	token_before[1] = "<";
	token_before[2] = ">";
	token_before[3] = "<<";
	token_before[4] = ">>";
	token_before[5] = "||";
	token_before[6] = "&&";
	token_before[7] = "|";

	return (token_before[n]);
}

int	ft_set_token(char *str)
{
	int	n;
	char	*token_before;

	n = 7;
	while (n > 0)
	{
		token_before = ft_token_before(n);
		if (!ft_strncmp(str, token_before, 2))
			return (n);
		n--;
	}
	return (n);
}
