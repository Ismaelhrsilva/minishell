/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/06/14 22:36:44 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_str_splitted(char *str)
{
	int	i;
	int	j;
	int count;

	count = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while ((ft_isalnum(str[j]) == 8 || str[j] == '_' || str[j] == '$')
			&&  str[j] != '\0')
		{
			if (j == i)
				count++;
			j++;
		}
		i = j;
		while ((ft_isalnum(str[j]) == 0 && str[j] != '_' && str[j] != '$')
			&&  str[j] != '\0')
		{
			count++;
			j++;
		}
		i = j;
	}
	return (count);
}

char	**ft_split_expand(char *str)
{
	char	**split;
	int	i;
	int	j;
	int	m;

	i = 0;
	j = 0;
	m = 0;
	split = ft_calloc(ft_count_str_splitted(str) + 1, sizeof(char **));
	while (str[i] != '\0')
	{
		while ((ft_isalnum(str[j]) == 8 || str[j] == '_' || str[j] == '$')
			&&  str[j] != '\0')
			j++;	
		if (str[i] != '\0')
			split[m++] = ft_substr(str, i, j - i);
		i = j;
		while ((ft_isalnum(str[j]) == 0 && str[j] != '_' && str[j] != '$')
			&&  str[j] != '\0')
			j++;	
		if (str[i] != '\0')
			split[m++] = ft_substr(str, i, j - i);
		//j++;
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
	int	i;
	char	*new_str;
	char	**split;

	i = 0;
	split = ft_split_expand(str);
	while (i < ft_count_matrix(split))
	{
		if (i == 0)
			new_str = ft_expand(split[i], shell);
		else
			new_str = ft_strjoin(new_str, ft_expand(split[i], shell));
		i++;
	}
	return (new_str);
}
