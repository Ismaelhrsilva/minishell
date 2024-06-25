/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/25 18:14:36 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_expand(char *str, t_vector *split, int i, int j)
{
	while (str[i] != '\0')
	{
		while ((ft_isalnum(str[j]) == 8) && str[j] != '\0')
			j++;
		if (str[i] != '\0' && j != i)
			ft_vector_push_back(split, ft_substr(str, i, j - i));
		i = j;
		if (str[j] == '$' && str[j + 1] == '?')
		{
			j++;
			j++;
			if (str[i] != '\0' && j != i)
				ft_vector_push_back(split, ft_substr(str, i, j - i));
			i = j;
		}
		if (str[j] == '$')
		{
			j++;
			while ((ft_isalnum(str[j]) == 8 || str[j] == '_' || str[j] == '?')
				&& str[j] != '\0')
				j++;
			if (str[i] != '\0' && j != i)
				ft_vector_push_back(split, ft_substr(str, i, j - i));
			i = j;
		}
		if ((ft_isalnum(str[j]) == 0 && str[j] != '$')
			&& str[j] != '\0')
			j++;
		if (str[i] != '\0' && j != i)
			ft_vector_push_back(split, ft_substr(str, i, j - i));
		i = j;
	}
}

char	ft_signal(t_vector *vector, int *i, char signal)
{
	if (ft_strchr("\'\"", ((char *)ft_vector_at(vector, *i))[0]))
	{
		if (ft_strchr((char *)ft_vector_at(vector, (*i)++), '\"'))
			signal = '\"';
		else
			signal = '\'';
	}
	return (signal);
}

char	*ft_expand_aux(t_shell *shell, t_vector *vector, int i, char signal)
{
	char	*final_str;
	char	*s;

	final_str = "";
	while (i < vector->size)
	{
		signal = ft_signal(vector, &i, signal);
		s = (char *)ft_vector_at(vector, i);
		while ((i < vector->size) && (signal != '\0' || !ft_strchr("\'\"",
					s[0])) && (s == NULL || signal != s[0]))
		{
			if (signal == '\'')
				final_str = ft_strjoin(final_str, ft_strdup(s));
			else
				final_str = ft_strjoin(final_str, ft_expand(s, shell));
			i++;
			s = (char *)ft_vector_at(vector, i);
		}
		signal = '\0';
	}
	return (final_str);
}

char	*ft_parse_expand(char *str, t_shell *shell)
{
	unsigned long int			i;
	char						signal;
	t_vector					*vector;

	i = 0;
	signal = '\0';
	vector = ft_vector_create();
	ft_split_expand(str, vector, 0, 0);
	return (ft_expand_aux(shell, vector, i, signal));
}
