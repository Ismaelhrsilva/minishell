/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/19 18:42:34 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vector	*ft_split_expand(char *str)
{
	t_vector	*split;
	int	i;
	int	j;

	i = 0;
	j = 0;
	split = ft_vector_create();
	while (str[i] != '\0')
	{
		while ((ft_isalnum(str[j]) == 8) &&  str[j] != '\0')
			j++;	
		if (str[i] != '\0' && j != i)
			ft_vector_push_back(split, ft_substr(str, i, j - i));
		i = j;
		while ((ft_isalnum(str[j]) == 8 || str[j] == '_' || str[j] == '$')
			&&  str[j] != '\0')
			j++;	
		if (str[i] != '\0' && j != i)
			ft_vector_push_back(split, ft_substr(str, i, j - i));
		i = j;
		if ((ft_isalnum(str[j]) == 0 && str[j] != '_' && str[j] != '$')
			&&  str[j] != '\0')
			j++;	
		if (str[i] != '\0' && j != i)
			ft_vector_push_back(split, ft_substr(str, i, j - i));
		i = j;
	}
	return (split);
}

char	*ft_find_expand(char *str, t_shell *shell)
{	
	int	i;
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
		if (ft_find_expand(&str[1], shell) != NULL)
			return (ft_find_expand(&str[1], shell));
	return (str);
}

char	*ft_parse_expand(char *str, t_shell *shell)
{
	int		i;
	char	signal;
	char	*new_str;
	char	*final_str;
	t_vector	*vector;
	char	*split;

	i = 0;
	signal = '\0';
	vector = ft_split_expand(str);
	final_str = "";
	while (i < vector->size)
	{
		if (i == 0)
			split = (char *)ft_vector_at(vector, i);
		if (ft_strchr("\'\"", split[0]))
		{
			if (ft_strchr(split, '\"'))
				signal = '\"';
			else
				signal = '\'';
			i++;
			split = (char *)ft_vector_at(vector, i);
		}
		while ((i < vector->size) &&
       (signal != '\0' || !ft_strchr("\'\"", split[0])) &&
       (split == NULL || signal != split[0]))
		{
			if (signal == '\'')
				final_str = ft_strjoin(final_str, ft_strdup(split));
			else
			{
				new_str = ft_expand(split, shell);
				final_str = ft_strjoin(final_str, new_str);
				//free(new_str);
			}
			i++;
			split = (char *)ft_vector_at(vector, i);
		}
		signal = '\0';
	}
	return (final_str);
}
