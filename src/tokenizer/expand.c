/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/10 20:31:19 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_signal(t_vector *vector, size_t *i, char signal)
{
	if (ft_strchr("\'\"", ((char *)ft_vector_at(vector, *i))[0]))
	{
		if (ft_strchr((char *)ft_vector_at(vector, (*i)++), '\"'))
			signal = '\"';
		else
			signal = '\'';
	}
	else
		signal = '\0';
	return (signal);
}

int	ft_empty_str(t_vector *vector)
{
	char	*str;
	char	*str_1;

	if (vector->size == 2)
	{
		str = ft_vector_at(vector, 0);
		str_1 = ft_vector_at(vector, 1);
		if (ft_strchr("\"\'", str[0]))
			if (ft_strchr("\"\'", str_1[0]))
				return (1);
	}
	return (0);
}

char	*ft_expand_aux(t_shell *shell, t_vector *vector, unsigned long int i,
		char signal)
{
	char	*final_str;
	char	*s;
	int		not_expanded;
	char	*temp;

	final_str = "";
	temp = "";
	not_expanded = 0;
	if (ft_empty_str(vector))
		return (ft_strdup(""));
	while (i < vector->size)
	{
		if (i == 0)
		{
			signal = ft_signal(vector, &i, signal);
			s = (char *)ft_vector_at(vector, i);
		}
		while ((i < vector->size) && (signal != '\0' || !ft_strchr("\'\"",
					s[0])) && (s == NULL || signal != s[0]))
		{
			if (signal == '\'')
			{
				final_str = ft_strjoin(temp, s);
				if (ft_strlen(temp) != 0)
					free(temp);
				temp = final_str;
				not_expanded++;
			}
			else if (ft_strncmp(ft_expand(s, shell), "0x1A", 4) != 0)
			{
				final_str = ft_strjoin(temp, ft_expand(s, shell));
				if (ft_strlen(temp) != 0)
					free(temp);
				temp = final_str;
				not_expanded++;
			}
			i++;
			s = (char *)ft_vector_at(vector, i);
		}
		if (s && ft_strchr("\'\"", s[0]))
		{
			if (i + 1 < vector->size)
				i++;
			signal = ft_signal(vector, &i, signal);
			s = (char *)ft_vector_at(vector, i);
		}
		else
			signal = '\0';
	}
	if (not_expanded == 0)
		return (ft_strdup("0x1A"));
	return (final_str);
}

char	*ft_parse_expand(char *str, t_shell *shell)
{
	unsigned long int	i;
	char				signal;
	t_vector			*vector;
	char				*result;

	i = 0;
	signal = '\0';
	vector = ft_vector_create();
	ft_split_expand(str, vector);
	result = ft_expand_aux(shell, vector, i, signal);
	clean_vector(vector);
	return (result);
}
