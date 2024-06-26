/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:17:19 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/01 19:41:18 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vector	*ft_construct_phrase(char **split, t_shell *shell)
{
	t_vector	*phrase;
	int			i;
	int			*token;
	t_vector	*word;

	(void)shell;
	phrase = ft_vector_create();
	if (!phrase)
		return (NULL);
	i = 0;
	while (split[i])
	{
		word = ft_vector_create();
		if (!word)
			return (NULL);
		//ft_vector_push_back(word, ft_parse_expand(split[i], shell));
		ft_vector_push_back(word, split[i]);
		token = malloc(sizeof(int));
		if (!token)
			return (NULL);
		*token = ft_set_token(split[i]);
		ft_vector_push_back(word, token);
		ft_vector_push_back(word, split[i]);
		ft_vector_push_back(phrase, word);
		i++;
	}
	return (phrase);
}

void	ft_free_phrase(t_vector *phrase)
{
	size_t	i;
	t_vector		*word;

	i = 0;
	if (!phrase)
		return ;
	while (i < phrase->size)
	{
		word = phrase->values[i];
		free(word);
		i++;
	}
	ft_vector_free(phrase);
}
