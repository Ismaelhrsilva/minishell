/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:30:18 by paranha           #+#    #+#             */
/*   Updated: 2024/06/29 19:31:56 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_print(t_vector *vars)
{
	unsigned long	i;
	char			*full_string;

	i = 0;
	while (i < ft_vector_size(vars))
	{
		full_string = ft_strdup(ft_value(vars, i, 3));
		if (ft_strchr(full_string, '='))
			ft_putendl_fd(full_string, STDOUT_FILENO);
		free(full_string);
		i++;
	}
}

void	ft_builtin_env(t_shell *shell, t_vector *cmd)
{
	if (cmd->size > 1)
		return ;
	else
		ft_env_print(shell->envp_dict);
}
