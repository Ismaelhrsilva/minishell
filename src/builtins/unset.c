/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:13:00 by paranha           #+#    #+#             */
/*   Updated: 2024/06/26 18:40:09 by paranha          ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_shell *shell, t_vector *cmd)
{
	int			i;
	char		*arg;

	g_status = EXIT_SUCCESS;
	i = 1;
	while (i < cmd->size)
	{
		arg = ft_value(cmd, i, 0);
		//printf("Unsetting variable: %s\n", arg);
		ft_env_delete(shell->envp_dict, arg);
		i++;
	}
}
