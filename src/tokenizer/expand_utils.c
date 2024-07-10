/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/10 18:19:28 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_expand(char *str, t_shell *shell)
{
	size_t	i;
	char	*key;

	i = 0;
	while (i < shell->envp_dict->size)
	{
		key = ft_value(shell->envp_dict, i, 0);
		if (ft_strncmp(key, str, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(str))
			return (ft_value(shell->envp_dict, i, 1));
		i++;
	}
	return (NULL);
}

char	*ft_expand(char *str, t_shell *shell)
{
	if (!str)
		return (NULL);
	if (str[0] == '$' && ft_strlen(&str[1]))
	{
		if (str[1] == '?' && ft_strlen(str) == 2)
			return (ft_itoa(ft_status(-1)));
		else if (ft_isdigit(str[1]))
			return (&str[2]);
		else if (ft_find_expand(&str[1], shell) != NULL)
			return (ft_find_expand(&str[1], shell));
		else if (ft_find_expand(&str[1], shell) == NULL)
			return ("0x1A");
	}
	return (str);
}

char	*ft_parse_expand_heredoc(char *str, t_shell *shell)
{
	size_t		i;
	char		*new_str;
	char		*final_str;
	char		*temp;
	t_vector	*vector;
	char		*split;
	int			not_expanded;

	i = 0;
	vector = ft_vector_create();
	ft_split_expand(str, vector, 0, 0);
	final_str = "";
	temp = "";
	not_expanded = 0;
	while (i < vector->size)
	{
		split = (char *)ft_vector_at(vector, i);
		new_str = ft_expand(split, shell);
		if (ft_strncmp(new_str, "0x1A", 4) != 0)
		{
			final_str = ft_strjoin(temp, new_str);
			if (ft_strlen(temp) != 0)
				free(temp);
			temp = final_str;
			not_expanded++;
		}
		i++;
	}
	i = 0;
	while (i < vector->size)
	{
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
	if (not_expanded == 0)
		return (ft_strdup("0x1A"));
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
	ft_split_expand(str, vector, 0, 0);
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
