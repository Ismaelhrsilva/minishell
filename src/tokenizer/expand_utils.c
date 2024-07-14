/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/14 17:55:26 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*status;

	if (!str)
		return (NULL);
	if (str[0] == '$' && ft_strlen(&str[1]))
	{
		if (str[1] == '?' && ft_strlen(str) == 2)
		{
			status = ft_itoa(ft_status(-1));
			return (status);
		}
		else if (ft_isdigit(str[1]))
			return (&str[2]);
		else if (ft_find_expand(&str[1], shell) != NULL)
			return (ft_find_expand(&str[1], shell));
		else if (ft_find_expand(&str[1], shell) == NULL)
			return ("0x1A");
	}
	return (str);
}

unsigned long int	ft_i(unsigned long int st)
{
	static unsigned long int	i;

	if (st != 9999)
		i = st;
	return (i);
}

char	*ft_signal_str(t_vector *vector, size_t *i)
{
	char	*signal;
	char	*str;

	str = (char *)ft_vector_at(vector, *i);
	if (str && ft_strchr("\'\"", str[0]))
	{
		(*i)++;
		if (str[0] == '\"')
			signal = "\"";
		else
			signal = "\'";
	}
	else
		signal = "\0";
	ft_i(*i);
	return (signal);
}
