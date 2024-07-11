/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/11 15:06:40 by ishenriq         ###   ########.fr       */
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

char	*ft_parse_expand_heredoc_aux(char **str, t_shell *shell,
		t_vector *vector)
{
	size_t		i;
	int			not_expanded;

	i = 0;
	not_expanded = 0;
	while (i < vector->size)
	{
		str[2] = (char *)ft_vector_at(vector, i);
		str[3] = ft_expand(str[2], shell);
		if (ft_strncmp(str[3], "0x1A", 4) != 0)
		{
			str[0] = ft_strjoin(str[1], str[3]);
			if (ft_strlen(str[1]) != 0)
				free(str[1]);
			str[1] = str[0];
			not_expanded++;
		}
		i++;
	}
	ft_clean_vector(vector);
	if (not_expanded == 0)
		return (ft_strdup("0x1A"));
	return (str[0]);
}

char	*ft_parse_expand_heredoc(char *s, t_shell *shell)
{
	t_vector	*vector;
	char		*str[4];
	char		*final_str;

	str[0] = "";
	str[1] = "";
	str[2] = "";
	str[3] = "";
	vector = ft_vector_create();
	ft_split_expand(s, vector);
	final_str = ft_parse_expand_heredoc_aux(str, shell, vector);
	return (final_str);
}

char	*ft_eliminate_signal(char *str, t_shell *shell)
{
	unsigned long int	i;
	char				signal;
	t_vector			*vector;
	char				*final_str;
	char				*s;
	char				*temp;
	char				*temp_2;

	i = 0;
	signal = '\0';
	vector = ft_vector_create();
	ft_split_expand(str, vector);
	final_str = "";
	temp = "";
	temp_2 = "";
	while (i < vector->size)
	{
		signal = ft_signal(vector, &i, signal);
		s = (char *)ft_vector_at(vector, i);
		while ((i < vector->size) && (signal != '\0' || !ft_strchr("\'\"",
					s[0])) && (s == NULL || signal != s[0]))
		{
			if (signal == '\'')
			{
				temp_2 = ft_strdup(s);
				final_str = ft_strjoin(temp, temp_2);
				free(temp_2);
				if (ft_strlen(temp) != 0)
					free(temp);
				temp = final_str;
			}
			else if (ft_strncmp(ft_expand(s, shell), "0x1A", 4) != 0)
			{
				temp_2 = ft_strdup(s);
				final_str = ft_strjoin(temp, temp_2);
				free(temp_2);
				if (ft_strlen(temp) != 0)
					free(temp);
				temp = final_str;
			}
			i++;
			s = (char *)ft_vector_at(vector, i);
		}
		signal = '\0';
	}
	i = 0;
	while (i < vector->size)
	{
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
	return (final_str);
}
