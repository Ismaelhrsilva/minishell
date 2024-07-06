/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:46:44 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/05 14:39:30 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_matrixreplace(char **s, char signal, char old_ch, char new_ch)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_replace_char_between_signal(s[i], signal, old_ch, new_ch);
		i++;
	}
}

t_vector	*ft_build_line_envp(char *str)
{
	t_vector	*line_dict;
	char		**split;
//	char		**split_values;

	line_dict = ft_vector_create();
	if (!line_dict)
		return ((t_vector *)0);
	split = ft_split(str, '=');
	ft_vector_push_back(line_dict, ft_strdup(split[0]));
	if (split[1])
	{
		ft_vector_push_back(line_dict, ft_strdup(split[1]));
		ft_replace_char_between_signal(split[1], '\'', ':', 0x1A);
		//split_values = ft_split(split[1], ':');
	//	ft_vector_push_back(line_dict, split_values);
		ft_vector_push_back(line_dict, ft_split(split[1], ':'));
		ft_matrixreplace(line_dict->values[2], '\'', 0x1A, ':');
	}
	else
	{
		ft_vector_push_back(line_dict, ft_strdup(""));
		ft_vector_push_back(line_dict, NULL);
	}
	ft_vector_push_back(line_dict, ft_strdup(str));
	ft_freesplit(split);
	return (line_dict);
}

void	ft_free_line_envp(t_vector *line_dict)
{
	if (line_dict)
	{
		free(line_dict->values[0]);
		free(line_dict->values[1]);
		if (line_dict->values[2])
			ft_freesplit(line_dict->values[2]);
		free(line_dict->values[3]);
		ft_vector_free(line_dict);
		//	ft_free_phrase(line_dict);
	}
}

t_vector	*ft_envp_dict(char **envp)
{
	t_vector	*envp_dict;
	int			i;
	t_vector	*line_dict;

	i = 0;
	envp_dict = ft_vector_create();
	if (!envp_dict)
		return (NULL);
	while (envp[i] != NULL)
	{
		line_dict = ft_build_line_envp(envp[i]);
		if (!line_dict)
		{
			ft_vector_free(envp_dict);
			return (NULL);
		}
		ft_vector_push_back(envp_dict, line_dict);
		i++;
	}
	return (envp_dict);
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

void	ft_envp(t_shell *shell)
{
	shell->envp_dict = ft_envp_dict(shell->envp);
	shell->path = ft_getenv(shell->envp_dict, "PATH");
	shell->path_splitted = ft_split(shell->path, ':');
}


void	ft_free_shell(t_shell *shell)
{
	if (shell)
	{
		//	get_next_line(-1);
		ft_free_envp_dict(shell->envp_dict);
		ft_freesplit(shell->path_splitted);
		// free(shell->path);
		free(shell);
	}
}
