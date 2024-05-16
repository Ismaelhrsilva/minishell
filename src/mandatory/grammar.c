/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/16 18:03:23 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static int	ft_redirects_following(t_phrase *phrase, int pos)
{
	if (ft_get_token(phrase, pos) & REDIRECTS)
		if (ft_get_token(phrase, pos + 1) & REDIRECTS)
			return (1);
	return (0);
}

void	ft_grammar_rules(t_phrase *phrase)
{
	int	n;
	int i;

	i = 0;
	n = phrase->size;
	while (i < n)
	{
		if (ft_redirects_following(phrase, i))
	  			ft_printf("Not allowed\n");
		/*if (ft_token_equal(phrase, i, REDIRECTS) && ft_token_equal(phrase, (i + 1), REDOUT))
	  			ft_printf("Not allowed\n");
		else if (ft_token_equal(phrase, i, REDOUT) && ft_token_equal(phrase, i + 1, REDIN))
	  			ft_printf("Not allowed\n");
		else if (ft_token_equal(phrase, i, REDIN) && ft_token_equal(phrase, i + 1, REDIN))
	  			ft_printf("Not allowed\n");
		else if (ft_token_equal(phrase, i, REDOUT) && ft_token_equal(phrase, i + 1, REDOUT))
	  			ft_printf("Not allowed\n");*/
		i++;
	}
}
