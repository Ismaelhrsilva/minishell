/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phrase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:17:19 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/03 20:37:04 by paranha          ###   ########.org.br   */
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
		// ft_vector_push_back(word, ft_parse_expand(split[i], shell));
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

//int	ft_is_inner_vector(void *ptr)
//{
//	t_vector	*vec;
//
//	if (ptr == NULL)
//		return (0);
//	vec = (t_vector *)ptr;
//	if (vec->size > vec->capacity || vec->capacity > 1000000)
//		return (0);
//	if (vec->values == NULL)
//		return (0);
//	return (1);
//}
//
//void	ft_vector_free_inner(t_vector *vector)
//{
//	size_t	i;
//
//	i = 0;
//	if (vector == NULL)
//		return ;
//	while (i < vector->size)
//	{
//		if (vector->values[i])
//		{
//			if (ft_is_inner_vector(vector->values[i]))
//				ft_vector_free((t_vector *)vector->values[i]);
//			else
//				free(vector->values[i]);
//		}
//		i++;
//	}
//	free(vector->values);
//	free(vector);
//}
//
//void	ft_free_phrase(t_vector *phrase)
//{
//	if (!phrase)
//		return ;
//	ft_vector_free_inner(phrase);
//}

// void	ft_free_phrase(t_vector *phrase)
//{
//	size_t	i;
//	t_vector		*word;
//
//	i = 0;
//	if (!phrase)
//		return ;
//	while (i < phrase->size)
//	{
//		word = phrase->values[i];
//		free(word);
//		i++;
//	}
//	ft_vector_free(phrase);
//}
