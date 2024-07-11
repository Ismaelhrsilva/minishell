/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/11 13:52:48 by ishenriq         ###   ########.fr       */
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
