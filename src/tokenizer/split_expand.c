/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:26:58 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/11 17:09:11 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_dollar_question(char *str, t_vector *split, t_index *idx)
{
	idx->j++;
	idx->j++;
	if (str[idx->i] != '\0' && idx->j != idx->i)
		ft_vector_push_back(split, ft_substr(str, idx->i, idx->j - idx->i));
	idx->i = idx->j;
}

void	process_dollar(char *str, t_vector *split, t_index *idx)
{
	idx->j++;
	while ((ft_isalnum(str[idx->j]) == 8 || str[idx->j] == '_'
			|| str[idx->j] == '?') && str[idx->j] != '\0')
		idx->j++;
	if (str[idx->i] != '\0' && idx->j != idx->i)
		ft_vector_push_back(split, ft_substr(str, idx->i, idx->j - idx->i));
	idx->i = idx->j;
}

void	process_alnum(char *str, t_vector *split, t_index *idx)
{
	if ((ft_isalnum(str[idx->j]) == 0 && str[idx->j] != '$')
		&& str[idx->j] != '\0')
		idx->j++;
	if (str[idx->i] != '\0' && idx->j != idx->i)
		ft_vector_push_back(split, ft_substr(str, idx->i, idx->j - idx->i));
	idx->i = idx->j;
}

void	ft_process_split(char *str, t_vector *split, t_index *idx)
{
	while (str[idx->i] != '\0')
	{
		while ((ft_isalnum(str[idx->j]) == 8) && str[idx->j] != '\0')
			idx->j++;
		if (str[idx->i] != '\0' && idx->j != idx->i)
			ft_vector_push_back(split, ft_substr(str, idx->i, idx->j - idx->i));
		idx->i = idx->j;
		if (str[idx->j] == '$' && str[idx->j + 1] == '?')
			process_dollar_question(str, split, idx);
		else if (str[idx->j] == '$')
			process_dollar(str, split, idx);
		else
			process_alnum(str, split, idx);
	}
}

void	ft_split_expand(char *str, t_vector *split)
{
	t_index	idx;

	idx.i = 0;
	idx.j = 0;
	if (!str)
		return ;
	ft_process_split(str, split, &idx);
}
