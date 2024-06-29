/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:13:00 by paranha           #+#    #+#             */
/*   Updated: 2024/06/29 20:41:40 by ishenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	ft_env_delete(t_vector *vars, char *name)
{
	unsigned long	i;
	t_vector		*line_dict;
	char			*identifier;

	if (!vars || !name)
		return ;
	i = 0;
	while (i < ft_vector_size(vars))
	{
		line_dict = ft_vector_at(vars, i);
		identifier = ft_vector_at(line_dict, 0);
		if (identifier && ft_strcmp(identifier, name) == 0)
		{
			ft_vector_erase(vars, i);
			return ;
		}
		i++;
	}
}

void	ft_builtin_unset(t_shell *shell, t_vector *cmd)
{
	int			i;
	char		*arg;

	g_status = EXIT_SUCCESS;
	i = 1;
	while (i < cmd->size)
	{
		arg = ft_value(cmd, i, 0);
		if (ft_is_valid_name(arg))
			ft_env_delete(shell->envp_dict, arg);
		else
		{
			ft_putstr_fd("not a valid identifier", STDOUT_FILENO);
			ft_status(1);
		}
		i++;
	}
}
