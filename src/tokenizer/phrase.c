/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:17:19 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/19 17:46:38 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vector	*ft_construct_phrase(char **split, t_shell *shell)
{
	t_vector	*phrase;
	int			i;
	int			*token;
	t_vector	*word;

	phrase = ft_vector_create();
	if (!phrase)
		return (NULL);
	i = 0;
	while (split[i])
	{
		word = ft_vector_create();
		if (!word)
			return (NULL);
		//if (ft_strchr("\'\"", split[i][0]))
		//	ft_eliminate_ch_corner(split[i]);
		split[i] = ft_parse_expand(split[i], shell);
		printf("%s\n", split[i]);
		ft_vector_push_back(word, split[i]);
		token = malloc(sizeof(int));
		if (!token)
			return (NULL);
		*token = ft_set_token(split[i]);
		ft_vector_push_back(word, token); 
		ft_vector_push_back(phrase, word);
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
}
