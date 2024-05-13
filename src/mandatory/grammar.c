/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:17:19 by ishenriq          #+#    #+#             */
/*   Updated: 2024/05/13 20:52:46 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/minishell.h"

typedef struct s_word
{
	char	*word;
	int		token;
}	t_word;

typedef struct s_phrase
{
	t_list	*words;
	int	size;
}	t_phrase;


static void	ft_construct_word(char *str, int n)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return ;
	word->word = str;
	word->token = n;
	return (word);
}

static void	ft_construct_phrase(char **split, int m)
{
	t_phrase *phrase;
	int	i;

	phrase = malloc(sizeof(t_phrase));
	if (!phrase)
		return ;
	i = 0;
	while (i < m--)
	{
		ft_construct_word(split[i], ft_set_token(split[i]));

	}
}
