/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenazer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:18:14 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/12 19:47:11 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static char	*ft_token(int n)
{
	char	**token;

	token = malloc(6 * sizeof(char **));
	token[0] = "REDIN";
	token[1] = "HEREDOC";
	token[2] = "PIPE";
	token[3] = "OR";
	token[4] = "AND";
	token[5] = "REDOUT";
	return (token[n]);
}

static char	*ft_token_before(int n)
{
	char	**token_before;

	token_before = malloc(6 * sizeof(char **));
	token_before[0] = "<";
	token_before[1] = "<<";
	token_before[2] = "|";
	token_before[3] = "||";
	token_before[4] = "&&";
	token_before[5] = ">";

	return (token_before[n]);
}

char	*ft_set_token(char *str)
{
	int	n;
	char	*token_before;
	char	*token;

	n = 7;
	token = NULL;
	while (n >= 0)
	{
		token_before = ft_token_before(n);
		if (!ft_strncmp(str, token_before, 2))
		{
			token = ft_token(n);
			break ;
		}
		n--;
	}
	if (!token)
		token = "Word";
	return (token);
}
