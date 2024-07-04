/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/04 11:43:45 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_split_expand(char *str, t_vector *split, int i, int j)
//{
//	while (str[i] != '\0')
//	{
//		while ((ft_isalnum(str[j]) == 8) && str[j] != '\0')
//			j++;
//		if (str[i] != '\0' && j != i)
//			ft_vector_push_back(split, ft_substr(str, i, j - i));
//		i = j;
//		if (str[j] == '$' && str[j + 1] == '?')
//		{
//			j++;
//			j++;
//			if (str[i] != '\0' && j != i)
//				ft_vector_push_back(split, ft_substr(str, i, j - i));
//			i = j;
//		}
//		if (str[j] == '$')
//		{
//			j++;
//			while ((ft_isalnum(str[j]) == 8 || str[j] == '_' || str[j] == '?')
//				&& str[j] != '\0')
//				j++;
//			if (str[i] != '\0' && j != i)
//				ft_vector_push_back(split, ft_substr(str, i, j - i));
//			i = j;
//		}
//		if ((ft_isalnum(str[j]) == 0 && str[j] != '$')
//			&& str[j] != '\0')
//			j++;
//		if (str[i] != '\0' && j != i)
//			ft_vector_push_back(split, ft_substr(str, i, j - i));
//		i = j;
//	}
//}

void	ft_split_expand(char *str, t_vector *split, int i, int j)
{
	char	*substr;

	while (str[i] != '\0')
	{
		while ((ft_isalnum(str[j]) == 8) && str[j] != '\0')
			j++;
		if (str[i] != '\0' && j != i)
		{
			substr = ft_substr(str, i, j - i);
			ft_vector_push_back(split, substr);
		}
		i = j;
		if (str[j] == '$' && str[j + 1] == '?')
		{
			j += 2;
			if (str[i] != '\0' && j != i)
			{
				substr = ft_substr(str, i, j - i);
				ft_vector_push_back(split, substr);
			}
			i = j;
		}
		if (str[j] == '$')
		{
			j++;
			while ((ft_isalnum(str[j]) == 8 || str[j] == '_' || str[j] == '?')
				&& str[j] != '\0')
				j++;
			if (str[i] != '\0' && j != i)
			{
				substr = ft_substr(str, i, j - i);
				ft_vector_push_back(split, substr);
			}
			i = j;
		}
		if ((ft_isalnum(str[j]) == 0 && str[j] != '$') && str[j] != '\0')
			j++;
		if (str[i] != '\0' && j != i)
		{
			substr = ft_substr(str, i, j - i);
			ft_vector_push_back(split, substr);
		}
		i = j;
	}
}

char	ft_signal(t_vector *vector, size_t *i, char signal)
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

	final_str = "";
	not_expanded = 0;
	if (ft_empty_str(vector))
		return ("");
	while (i < vector->size)
	{
		signal = ft_signal(vector, &i, signal);
		s = (char *)ft_vector_at(vector, i);
		while ((i < vector->size) && (signal != '\0' || !ft_strchr("\'\"",
					s[0])) && (s == NULL || signal != s[0]))
		{
			if (signal == '\'')
			{
				final_str = ft_strjoin(final_str, ft_strdup(s));
				not_expanded++;
			}
			else if (ft_strncmp(ft_expand(s, shell), "0x1A", 4) != 0)
			{
				final_str = ft_strjoin(final_str, ft_expand(s, shell));
				not_expanded++;
			}
			i++;
			s = (char *)ft_vector_at(vector, i);
		}
		signal = '\0';
	}
	if (not_expanded == 0)
		return ("0x1A");
	return (final_str);
}

// char	*ft_parse_expand(char *str, t_shell *shell)
//{
//	unsigned long int			i;
//	char						signal;
//	t_vector					*vector;
//
//	i = 0;
//	signal = '\0';
//	vector = ft_vector_create();
//	ft_split_expand(str, vector, 0, 0);
//	return (ft_expand_aux(shell, vector, i, signal));
//}

void	clean_vector(t_vector *vector)
{
	size_t	i;

	for (i = 0; i < vector->size; i++)
	{
		free(ft_vector_at(vector, i));
	}
	ft_vector_free(vector);
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
	ft_split_expand(str, vector, 0, 0);
	result = ft_expand_aux(shell, vector, i, signal);
	clean_vector(vector);
	return (result);
}

// works like a charm
// char	*ft_parse_expand(char *str, t_shell *shell)
//{
//    unsigned long int	i;
//    char				signal;
//    t_vector			*vector;
//    char                *result;
//
//    i = 0;
//    signal = '\0';
//    vector = ft_vector_create();
//    ft_split_expand(str, vector, 0, 0);
//    result = ft_expand_aux(shell, vector, i, signal);
//    ft_vector_free(vector);
//    return (result);
//}
