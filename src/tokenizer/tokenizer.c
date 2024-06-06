/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:18:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/05 19:35:32 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_token(char *str)
{
	int	n;
	const char	*tokens[10] = {"<", ">", "<<", ">>", "||", "&&", "|", "(", ")", 0};

	n = 0;
	while (tokens[n])
	{
		if (ft_strlen(str) <= 2 && ft_strncmp(str, tokens[n], 3) == 0)
			return (1 << n);
			//return (ft_power(2, (n)));
		n++;
	}
	return (0);
}
