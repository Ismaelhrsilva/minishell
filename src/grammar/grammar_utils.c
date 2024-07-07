/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:12 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/07 14:39:31 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

int	ft_count_token(t_vector *phrase, int token)
{
	int				count;
	size_t	i;

	i = 0;
	count = 0;
	while (i < phrase->size)
	{
		if (ft_value_int(phrase, i, 1) == token)
			count++;
		i++;
	}
	return (count);
}

int	ft_pos_token(t_vector *phrase, int start, int end, int token)
{
	int			pos;

	pos = start;
	while (pos < end)
	{
		if (ft_value_int(phrase, pos, 1) & token)
			return (pos);
		pos++;
	}
	return (-1);
}

int	ft_pos_token_back(t_vector *phrase, int token)
{
	int	pos;

	pos = phrase->size - 1;
	while (pos >= 0)
	{
		if (ft_value_int(phrase, pos, 1) & token)
			return (pos);
		pos--;
	}
	return (-1);
}

int	error(int status)
{
	if (status)
	{
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		ft_status(2);
		return (true);
	}
	return (false);
}
