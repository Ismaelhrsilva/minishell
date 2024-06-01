/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:17:19 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/01 14:26:27 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*vector_value(t_vector *vector, unsigned long index)
{
	return (vector->values[index]);
}

t_vector	*ft_construct_phrase(char **split)
{
	t_vector	*phrase;
	int			i;
	t_vector	*word;
	t_vector	*words;

	phrase = ft_vector_create();
	if (!phrase)
		return (NULL);
	i = 0;
	while (split[i])
	{
		word = ft_vector_create();
		if (!word)
		{
			return (NULL);
		}
		ft_vector_push_back(word, split[i]);
		ft_vector_push_back(word, ft_set_token(split[i]));
		ft_vector_push_back(phrase, word);
		i++;
	}
	i = 0;
	
	while (i < ft_vector_size(phrase))
	{
		t_vector *word;
		//word = vector_value(phrase, i); 
		word = phrase->values[i];
		ft_printf("----------------------------------------------\n");
		ft_printf("word: %s\n", word->values[0]);
		ft_printf("token: %d\n", word->values[1]);
		ft_printf("----------------------------------------------\n");
		i++;
	}
	return (phrase);
}

void	ft_free_phrase(t_vector *phrase)
{
	unsigned long	i;
	t_vector		*word;

	i = 0;
	if (!phrase)
		return ;
	while (i < ft_vector_size(phrase))
	{
		word = phrase->values[i];
		free(word);
		i++;
	}
	ft_vector_free(phrase);
	//free(phrase);
}
