/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:12:24 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/16 19:08:22 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_final_str(char **str, char *s, int *not_expanded)
{
	str[0] = ft_strjoin(str[1], s);
	if (ft_strlen(str[1]) != 0)
		free(str[1]);
	if (str[2] && ft_strlen(str[2]) > 1 && str[2][1] == '?')
		free(str[3]);
	str[1] = str[0];
	*not_expanded = *not_expanded + 1;
	return (str[0]);
}

void	ft_process_token(char **str, int *not_expanded,
		t_vector *vector, t_shell *shell)
{
	unsigned long int	i;

	i = ft_i(9999);
	while (i < vector->size && str[2] != NULL && str[2][0] != str[4][0])
	{
		str[3] = ft_expand(str[2], shell);
		if (str[4][0] == '\'')
			str[0] = ft_final_str(str, str[2], not_expanded);
		else if (ft_strncmp(str[3], "0x1A", 4) != 0)
			str[0] = ft_final_str(str, str[3], not_expanded);
		(i)++;
		str[2] = (char *)ft_vector_at(vector, i);
		if (str[2] && str[4][0] == '\0'
			&& (str[2][0] == '\"' || str[2][0] == '\''))
			break ;
		if (str[2] && str[4][0] != '\0' && str[2][0] == str[4][0])
		{
			(i)++;
			break ;
		}
	}
	ft_i(i);
}

void	ft_process_quotes(char **str,
		t_vector *vector)
{
	unsigned long int	i;

	i = ft_i(9999);
	while (i < vector->size)
	{
		i = ft_i(9999);
		str[4] = ft_signal_str(vector, &i);
		str[2] = (char *)ft_vector_at(vector, ft_i(9999));
		if (str[2] && str[4][0] == str[2][0])
		{
			str[4] = "\0";
			ft_i(i + 1);
			str[2] = (char *)ft_vector_at(vector, ft_i(9999));
			if (str[2] && !(str[2][0] != '\'' || str[2][0] != '\"'))
				break ;
		}
		else
			break ;
	}
	ft_i(i);
}

char	*ft_expand_aux(t_shell *shell, t_vector *vector, unsigned long int i)
{
	char	*str[5];
	int		not_expanded;

	str[0] = "";
	str[1] = "";
	str[2] = "";
	str[3] = "";
	str[4] = "";
	not_expanded = 0;
	(void ) i;
	if (ft_empty_str(vector))
		return (ft_strdup(""));
	while (ft_i(9999) < vector->size)
	{
		ft_process_quotes(str, vector);
		ft_process_token(str, &not_expanded, vector, shell);
	}
	if (not_expanded == 0)
		return (ft_strdup("0x1A"));
	return (str[0]);
}

char	*ft_parse_expand(char *str, t_shell *shell)
{
	unsigned long int	i;
	t_vector			*vector;
	char				*result;

	i = ft_i(0);
	vector = ft_vector_create();
	ft_split_expand(str, vector);
	result = ft_expand_aux(shell, vector, i);
	ft_clear_vector(vector);
	return (result);
}
