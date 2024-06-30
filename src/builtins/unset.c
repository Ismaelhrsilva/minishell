/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:13:00 by paranha           #+#    #+#             */
/*   Updated: 2024/06/30 20:32:28 by paranha          ###   ########.org.br   */
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

int	ft_is_valid_unset(char *name)
{
	int	i;

	if (!isalpha(name[0]) && name[0] != '_')
	{
		ft_status(1);
		return (0);
	}
	i = 1;
	while (name[i] != '\0')
	{
		if (!isalnum(name[i]) && name[i] != '_')
		{
			ft_status(1);
			return (0);
		}
		i++;
	}
	return (1);
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
		if (ft_is_valid_unset(arg))
			ft_env_delete(shell->envp_dict, arg);
		else
			ft_status(0);
		i++;
	}
}
