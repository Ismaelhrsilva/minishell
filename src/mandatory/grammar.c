/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/15 19:55:47 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

static int	ft_get_token(t_phrase *phrase, int pos)
{
	int	token;

	while (phrase->words && pos-- >= 0)
	{
		token = ((t_word *)phrase->words->content)->token;
		phrase->words = phrase->words->next;
	}
	return (token);
}

void	ft_grammar_rules(t_phrase *phrase)
{
	int	n;
	int i;

	i = 0;
	n = phrase->size;
	while (n-- > 0)
	{
		if (ft_get_token(phrase, i) == REDIN && ft_get_token(phrase, i + 1) == REDOUT)
	  			ft_printf("Not allowed\n");
		else if (ft_get_token(phrase, i) == REDOUT && ft_get_token(phrase, i + 1) == REDIN)
	  			ft_printf("Not allowed\n");
		else if (ft_get_token(phrase, i) == REDIN && ft_get_token(phrase, i + 1) == REDIN)
	  			ft_printf("Not allowed\n");
		else if (ft_get_token(phrase, i) == REDOUT && ft_get_token(phrase, i + 1) == REDOUT)
	  			ft_printf("Not allowed\n");
		i++;
	}
}
