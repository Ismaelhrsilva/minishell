/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:09 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/10 19:02:17 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freephrase(t_vector *vector)
{
	size_t		i;
	size_t		j;
	t_vector	*innervector;

	i = 0;
	if (!vector)
		return ;
	while (i < vector->size)
	{
		j = 0;
		innervector = ((t_vector *)vector->values[i]);
		while (j < innervector->size)
		{
			free(((t_vector *)vector->values[i])->values[j]);
			j++;
		}
		free(((t_vector *)vector->values[i])->values);
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
}

void	ft_freephrase_2(t_vector *vector)
{
	size_t	i;

	i = 0;
	if (!vector)
		return ;
	while (i < vector->size)
	{
		free(((t_vector *)vector->values[i])->values[0]);
		free(((t_vector *)vector->values[i])->values[2]);
		free(((t_vector *)vector->values[i])->values);
		free(vector->values[i]);
		i++;
	}
	free(vector->values);
	free(vector);
}

void	ft_free_envp_dict(t_vector *envp_dict)
{
	size_t	i;

	if (envp_dict)
	{
		i = 0;
		while (i < envp_dict->size)
		{
			ft_free_line_envp(envp_dict->values[i]);
			i++;
		}
		ft_vector_free(envp_dict);
	}
}

void	ft_free_shell(t_shell *shell)
{
	if (shell)
	{
		ft_free_envp_dict(shell->envp_dict);
		ft_freesplit(shell->path_splitted);
		free(shell);
	}
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		free(matrix[i++]);
	free(matrix);
}
