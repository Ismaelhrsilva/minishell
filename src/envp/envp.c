/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:46:44 by ishenriq          #+#    #+#             */
/*   Updated: 2024/07/01 19:12:11 by paranha          ###   ########.org.br   */
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

	line_dict = ft_vector_create();
	if (!line_dict)
		return ((t_vector *)0);
	split = ft_split(str, '=');
	ft_vector_push_back(line_dict, ft_strdup(split[0]));
	if (split[1])
	{
		ft_vector_push_back(line_dict, ft_strdup(split[1]));
		ft_replace_char_between_signal(split[1], '\'', ':', 0x1A);
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

t_vector	*ft_envp_dict(char **envp)
{
	t_vector	*envp_dict;
	int			i;

	i = 0;
	envp_dict = ft_vector_create();
	while (envp[i] != NULL)
		ft_vector_push_back(envp_dict, ft_build_line_envp(envp[i++]));
	return (envp_dict);
}

void	ft_envp(t_shell *shell)
{
	int			i;

	i = 0;
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
			shell->path = shell->envp[i];
		i++;
	}
	shell->path_splitted = ft_split(shell->path, ':');
	shell->envp_dict = ft_envp_dict(shell->envp);
}
